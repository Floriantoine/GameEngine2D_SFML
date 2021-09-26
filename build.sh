#!/bin/bash

WORK_DIR="$(dirname "$(readlink -f "$0")")"
BUILD_DIR="$WORK_DIR/build"
CONAN_PROFILE="$WORK_DIR/conanprofile"

mkdir -p "$BUILD_DIR" && \
cd "$BUILD_DIR" && \
conan install "$WORK_DIR" --build=missing --profile="$CONAN_PROFILE" && \
cmake "$WORK_DIR" -G "Unix Makefiles" && \
cmake --build "$BUILD_DIR" -j 8
