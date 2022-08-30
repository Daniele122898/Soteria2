#!/bin/bash
mkdir cmake-build-debug
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S ./ -B ./cmake-build-debug

