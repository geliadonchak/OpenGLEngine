#!/bin/bash

cd "$(dirname "$0")"
lcov -t "OpenGLEngineTests" --no-external -o math_libraries.info -c -d .
genhtml -o report math_libraries.info
rm math_libraries.info
xdg-open ./report/index.html &