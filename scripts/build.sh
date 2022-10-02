#!/bin/bash

DEBUG_BUILD_PATH='../debug_build'
RELEASE_BUILD_PATH='../release_build'

echo "Performing clean builds..."
echo "  Building debug inside debug_build/"
echo "  Building release inside release_build/"
echo -e ""

[ -d ${DEBUG_BUILD_PATH} ] && rm -rf ${DEBUG_BUILD_PATH}
[ -d ${RELEASE_BUILD_PATH} ] && rm -rf ${RELEASE_BUILD_PATH}

cmake -S ../ -B ${DEBUG_BUILD_PATH} -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
cmake --build ${DEBUG_BUILD_PATH} --target all

cmake -S ../ -B ${RELEASE_BUILD_PATH} -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build ${RELEASE_BUILD_PATH} --target all