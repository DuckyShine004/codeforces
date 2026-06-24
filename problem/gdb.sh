#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 <program>"
  exit 1
fi

PROGRAM="$1"
INPUT="cp.in"

gdb -ex "run < $INPUT" "$PROGRAM"
