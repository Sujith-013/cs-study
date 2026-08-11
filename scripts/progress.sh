#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
DONE=$(grep -c '^\s*- \[x\]' README.md || true)
TODO=$(grep -c '^\s*- \[ \]' README.md || true)
TOTAL=$((DONE + TODO))
[ "$TOTAL" -eq 0 ] && { echo "no checkboxes found"; exit 0; }
PCT=$((DONE * 100 / TOTAL)); BARS=$((PCT / 5))
printf '['
for i in $(seq 1 20); do [ "$i" -le "$BARS" ] && printf '#' || printf '.'; done
printf ']  %d/%d  (%d%%)\n' "$DONE" "$TOTAL" "$PCT"
