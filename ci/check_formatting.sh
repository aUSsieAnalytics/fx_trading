#!/bin/bash
set -e
clang-format --dry-run --Werror $(find . -name "*.cpp" -o -name "*.h")
