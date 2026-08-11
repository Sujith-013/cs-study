#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
TODAY="log/$(date +%F).md"
if [ ! -e "$TODAY" ]; then
  sed "s/YYYY-MM-DD/$(date +%F)/" log/TEMPLATE.md > "$TODAY"
  echo "created $TODAY"
fi
${EDITOR:-vi} "$TODAY"
