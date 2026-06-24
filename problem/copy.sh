#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: <filename>"
  exit 1
fi

FILENAME="$1.cpp"

if [ ! -f "$FILENAME" ]; then
  echo "File $FILENAME does not exist."
  exit 1
fi

xclip -selection clipboard < "$FILENAME"
