#!/bin/sh

gcc --version
g++ --version

if [ "$DISTRO" = "ubuntu" ]; then
	# Download and unzip the sonarcloud build wrapper
	curl -LsS https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip > build-wrapper-linux-x86.zip
	unzip build-wrapper-linux-x86.zip
	export SONARCLOUD_DIR=$PWD/build-wrapper-linux-x86
fi

export CI_PROJECT_DIR=/pdalc
export CI_PROJECT_NAME=pdal-c
export TARGET_PLATFORM=$DISTRO-`uname -m`-$BUILD_TYPE
echo "Building $CI_PROJECT_NAME ($TRAVIS_BRANCH-$TRAVIS_COMMIT) for $TARGET_PLATFORM"
rm -rf "$CI_PROJECT_DIR/build/$TARGET_PLATFORM" 
mkdir -p "$CI_PROJECT_DIR/build/$TARGET_PLATFORM"
cd "$CI_PROJECT_DIR/build/$TARGET_PLATFORM"
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DPDALC_GCC_PARAM_GGC_MIN_HEAPSIZE=8192 "$CI_PROJECT_DIR"

if [ "$DISTRO" = "ubuntu" ]; then
	$SONARCLOUD_DIR/build-wrapper-linux-x86-64 --out-dir $CI_PROJECT_DIR/bw-output make
else
	make
fi
make coverage_pdalc