#!/bin/bash

cd "$(dirname "$0")"
lcov -t "MathLibraries" --no-external -o math_libraries.info -c -d .
lcov --remove math_libraries.info 'opengl/catch.hpp' -o math_libraries_filtered.info
genhtml -o report math_libraries_filtered.info
rm math_libraries.info
rm math_libraries_filtered.info
xdg-open ./report/index.html