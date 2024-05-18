#!/bin/bash
set -e

# Remove previous build directory
rm -rf build
mkdir build && cd build

# Install dependencies via Conan
conan install .. --build=missing

# Generate build system files with CMake
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=../conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release

# Build the project
cmake --build .
