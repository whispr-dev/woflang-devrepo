#!/usr/bin/env bash
set -euo pipefail

# absolute path to the folder this script is in
SCRIPT_DIR="$(cd -- "$(dirname -- "$0")" && pwd)"
EXE_DIR="$SCRIPT_DIR/build/bin"
EXE="$EXE_DIR/woflang.exe"

if [[ ! -x "$EXE" ]]; then
  echo "missing $EXE — build first: cmake -S . -B build -G Ninja && cmake --build build" >&2
  exit 1
fi

cd "$EXE_DIR"
exec "$EXE" "$@"
