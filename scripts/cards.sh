#!/usr/bin/env bash
# Extract Anki cards from every notes/NN-*/README.md "## 8. Cards" section and
# write them to reference/cards.tsv in Anki's tab-separated import format
# (front<TAB>back, one card per line), deduplicated.
#
# A card line looks like: "Question :: Answer" -- everything before the
# first "::" is the front, everything after is the back. Blank lines and
# comment lines (<!-- ... -->) are skipped. Works from any directory.
set -euo pipefail
cd "$(dirname "$0")/.."

out="reference/cards.tsv"
tmp="$(mktemp)"
trap 'rm -f "$tmp"' EXIT

for f in notes/*/README.md; do
  awk '
  /^(## |### |#### )/ {
    in_cards = ($0 ~ /^## 8\. Cards/)
    next
  }
  in_cards {
    line = $0
    gsub(/^[ \t]+|[ \t]+$/, "", line)
    if (line == "" || line ~ /^<!--/) next
    pos = index(line, "::")
    if (pos == 0) next
    q = substr(line, 1, pos - 1)
    a = substr(line, pos + 2)
    gsub(/^[ \t]+|[ \t]+$/, "", q)
    gsub(/^[ \t]+|[ \t]+$/, "", a)
    if (q != "" && a != "") print q "\t" a
  }
  ' "$f"
done | sort -u > "$tmp"

mv "$tmp" "$out"
echo "wrote $(wc -l < "$out") cards to $out"
