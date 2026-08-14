#!/usr/bin/env bash
# Reports session streak stats from log/YYYY-MM-DD.md filenames.
#
# "Current streak" is the run of consecutive logged days ending at the most
# recent log, counted only if that log is from today or yesterday -- an older
# last session means the streak is broken, so current streak reads 0 even
# though a longest streak still shows in the record.
set -euo pipefail
cd "$(dirname "$0")/.."

day_num() {
  echo $(( $(TZ=UTC date -d "$1" +%s) / 86400 ))
}

shopt -s nullglob
dates=()
for f in log/*.md; do
  base="$(basename "$f" .md)"
  [ "$base" = "TEMPLATE" ] && continue
  [[ "$base" =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}$ ]] || continue
  dates+=("$base")
done

total=${#dates[@]}

if [ "$total" -eq 0 ]; then
  echo "No sessions logged yet."
  exit 0
fi

IFS=$'\n' sorted=($(sort <<<"${dates[*]}")); unset IFS

longest=1
run=1
prev_day="$(day_num "${sorted[0]}")"

for ((i = 1; i < total; i++)); do
  d="$(day_num "${sorted[i]}")"
  if [ "$d" -eq $((prev_day + 1)) ]; then
    run=$((run + 1))
  else
    run=1
  fi
  [ "$run" -gt "$longest" ] && longest="$run"
  prev_day="$d"
done

last_day="$prev_day"
today_day="$(day_num "$(date +%F)")"
days_since=$((today_day - last_day))

current=0
[ "$days_since" -le 1 ] && current="$run"

printf 'Current streak:          %d day(s)\n' "$current"
printf 'Longest streak:          %d day(s)\n' "$longest"
printf 'Total days logged:       %d\n' "$total"
printf 'Days since last session: %d\n' "$days_since"
