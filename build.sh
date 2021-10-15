#!/bin/bash

WORK_DIR="$(dirname "$(readlink -f "$0")")"
BUILD_DIR="$WORK_DIR/build"

mkdir -p "$BUILD_DIR"
cmake -S "$WORK_DIR" -B "$BUILD_DIR"
cmake --build "$BUILD_DIR"
