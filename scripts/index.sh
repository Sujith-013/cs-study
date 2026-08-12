#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."

# Count regular files under $1, excluding .gitkeep. 0 if the directory
# doesn't exist.
count_files() {
  local dir="$1"
  [ -d "$dir" ] || { echo 0; return; }
  find "$dir" -type f ! -name '.gitkeep' | wc -l
}

# Module number -> title, parsed from README.md's own headings:
# "### N. Title — `NN-slug`" or "#### N.M Title — `NN-slug`".
declare -A TITLE
while IFS=$'\t' read -r num title; do
  TITLE["$num"]="$title"
done < <(awk '
/^(## |### |#### )/ {
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
        num = substr(slug, 1, 2)
        printf "%s\t%s\n", num, title
      }
    }
  }
}
' README.md)

printf '  %-3s %-30s %-16s %5s %8s %10s\n' \
  "mod" "title" "status" "cpp" "python" "problems"

shopt -s nullglob
for notes_dir in notes/[0-9][0-9]-*/; do
  slug="$(basename "$notes_dir")"
  num="${slug:0:2}"
  title="${TITLE[$num]:-}"

  readme="notes/$slug/README.md"
  status="unknown"
  if [ -f "$readme" ]; then
    line="$(grep -m1 '^\*\*Status:\*\*' "$readme" || true)"
    if [ -n "$line" ]; then
      status="${line#*\*\*Status:\*\*}"
      status="$(echo "$status" | sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//')"
    fi
  fi

  cpp_count=$(count_files "src/cpp/$slug")
  py_count=$(count_files "src/python/$slug")
  problems_count=$(count_files "problems/$slug")

  printf '  %-3s %-30s %-16s %5s %8s %10s\n' \
    "$num" "$title" "$status" "$cpp_count" "$py_count" "$problems_count"
done
