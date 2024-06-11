#!/bin/bash

command -v clang-tidy >/dev/null 2>&1 || { echo "clang-tidy is required but it's not installed. Aborting." >&2; exit 1; }
clang-tidy -p build/linux --format-style='file' include/smol/**.h port/*.cpp unit_test/*.cpp
