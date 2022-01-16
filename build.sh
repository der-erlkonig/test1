#!/usr/bin/bash
./manual.sh
mkdir build
cmake -B build "$@"
cmake --build build
cd build && ctest -C Release && cd ..
cmake --install build
rm -rf build