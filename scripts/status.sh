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

printf '  %-22s %-14s %5s %8s %10s\n' "module" "notes" "cpp" "python" "problems"

shopt -s nullglob
for notes_dir in notes/[0-9][0-9]-*/; do
  slug="$(basename "$notes_dir")"

  status="missing"
  readme="notes/$slug/README.md"
  if [ -f "$readme" ]; then
    if grep -qE '^\*\*Status:\*\* *not started' "$readme"; then
      status="not started"
    else
      status="started"
    fi
  fi

  cpp_count=$(count_files "src/cpp/$slug")
  py_count=$(count_files "src/python/$slug")
  problems_count=$(count_files "problems/$slug")

  printf '  %-22s %-14s %5s %8s %10s\n' \
    "$slug" "$status" "$cpp_count" "$py_count" "$problems_count"
done
