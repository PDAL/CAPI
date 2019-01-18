#!/bin/sh

gcc --version
g++ --version

set CI_PROJECT_DIR=/pdalc
set CI_PROJECT_NAME=pdal-c
set BUILD_TYPE=Release

export TARGET_PLATFORM=`uname`-`arch`-$BUILD_TYPE
#echo "Building $CI_PROJECT_NAME ($TRAVIS_BRANCH branch) for $TARGET_PLATFORM"
rm -rf "$CI_PROJECT_DIR/build/$TARGET_PLATFORM" 
mkdir -p "$CI_PROJECT_DIR/build/$TARGET_PLATFORM"
cd "$CI_PROJECT_DIR/build/$TARGET_PLATFORM"
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DPDALC_GCC_PARAM_GGC_MIN_HEAPSIZE=8192 "$CI_PROJECT_DIR"
make
make coverage_pdalc