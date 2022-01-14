#!/usr/bin/bash
mkdir build
cmake -B build "$@"
cmake --build build
cd build && ctest -C Release && cd ..
cmake --install build
rm -rf build