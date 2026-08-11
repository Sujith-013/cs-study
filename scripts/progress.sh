#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."

DONE=$(grep -c '^\s*- \[x\]' README.md || true)
TODO=$(grep -c '^\s*- \[ \]' README.md || true)
TOTAL=$((DONE + TODO))
if [ "$TOTAL" -eq 0 ]; then
  echo "no checkboxes found"
  exit 0
fi
PCT=$((DONE * 100 / TOTAL)); BARS=$((PCT / 5))
printf '['
for i in $(seq 1 20); do [ "$i" -le "$BARS" ] && printf '#' || printf '.'; done
printf ']  %d/%d  (%d%%)\n' "$DONE" "$TOTAL" "$PCT"

echo
echo "Per-module breakdown:"

# Each module is a "### N. Title — \`NN-slug\`" or "#### N.M Title — \`NN-slug\`"
# heading in README.md. A module's checkboxes are every "- [ ]" / "- [x]"
# line (at any indent) between its heading and the next heading of any
# level -- headings that aren't modules (section dividers like "### 2. Data
# structures", or "## Optional (after the core)") just end the previous
# module's tally without starting a new one.
awk '
function flush() {
  if (cur_num != "") {
    if (cur_total == 0) {
      printf "  %-2s %-30s   no checkboxes\n", cur_num, cur_title
    } else {
      pct = int(cur_done * 100 / cur_total)
      printf "  %-2s %-30s %2d/%-3d (%3d%%)\n", cur_num, cur_title, cur_done, cur_total, pct
    }
  }
}
/^(## |### |#### )/ {
  flush()
  cur_num = ""; cur_title = ""; cur_done = 0; cur_total = 0

  line = $0
  pos1 = index(line, "`")
  if (pos1 > 0) {
    pos2 = index(substr(line, pos1 + 1), "`")
    if (pos2 > 0) {
      slug = substr(line, pos1 + 1, pos2 - 1)
      if (slug ~ /^[0-9][0-9]-/) {
        title = substr(line, 1, pos1 - 1)
        sub(/^#+ +[0-9]+(\.[0-9]+)?\.? +/, "", title)
        sub(/[ \t—-]+$/, "", title)
        cur_num = substr(slug, 1, 2)
        cur_title = title
      }
    }
  }
  next
}
{
  if (cur_num != "") {
    if ($0 ~ /^[ \t]*- \[x\]/) { cur_done++; cur_total++ }
    else if ($0 ~ /^[ \t]*- \[ \]/) { cur_total++ }
  }
}
END { flush() }
' README.md
