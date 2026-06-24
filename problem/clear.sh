#!/usr/bin/env bash

find . -maxdepth 1 -type f -exec file {} + | grep "ELF" | cut -d: -f1 | xargs -r rm
