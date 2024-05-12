#!/bin/bash
rm -rf build
mkdir build && cd build
conan install .. --build=missing
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .