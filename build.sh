#!/usr/bin/bash
mkdir build
cmake -B build "$@"
cmake --build build
cmake --install build
rm -rf build