#!/bin/bash
#
# Format source code with Google C++ style
find src -name '*.cc' -or -name '*.h' | xargs clang-format -style=Google -i
