#!/usr/bin/env bash
# "Where am I" dashboard: run before starting a session. Prints the most
# recent log's Topic and Tomorrow lines, then progress.sh and streak.sh.
set -euo pipefail
cd "$(dirname "$0")/.."

echo "=== Last session ==="
shopt -s nullglob
logs=()
for f in log/*.md; do
  base="$(basename "$f" .md)"
  [ "$base" = "TEMPLATE" ] && continue
  [[ "$base" =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}$ ]] || continue
  logs+=("$f")
done

if [ "${#logs[@]}" -eq 0 ]; then
  echo "No sessions logged yet."
else
  IFS=$'\n' sorted=($(sort <<<"${logs[*]}")); unset IFS
  last="${sorted[$((${#sorted[@]} - 1))]}"
  echo "Log: $last"

  topic="$(grep -m1 '^\*\*Topic:\*\*' "$last" | sed 's/^\*\*Topic:\*\* *//')"
  echo "Topic: ${topic:-(not filled in)}"

  echo "Tomorrow:"
  awk '
  /^## Tomorrow/ { in_section = 1; next }
  /^## / { in_section = 0 }
  in_section { print }
  ' "$last"
fi

echo
echo "=== Progress ==="
./scripts/progress.sh

echo
echo "=== Streak ==="
./scripts/streak.sh
