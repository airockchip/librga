#!/bin/bash

SCRIPT_DIR=$(cd $(dirname ${BASH_SOURCE[0]}); pwd)
BUILD_DIR=build_android_ndk
BINARY_DIR=$BUILD_DIR/bin
LIBRGA_PATH=${SCRIPT_DIR}/../../libs

rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR
mkdir -p $BINARY_DIR
pushd $BUILD_DIR

ANDROID_NDK_HOME=/home/yqw/library/AndroidNDK/android-ndk-r16b
CMAKE_ANDROID=/home/yqw/library/cmake_3.20.1/cmake-3.20.1/bin/cmake

${CMAKE_ANDROID} -DCMAKE_BUILD_TARGET=android_ndk \
      -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
      -DANDROID_NDK=$ANDROID_NDK_HOME \
      -DANDROID_ABI=arm64-v8a \
      -DANDROID_TOOLCHAIN=clang \
      -DANDROID_PLATFORM=android-24 \
      -DANDROID_STL=c++_shared \
	  -DBUILD_WITH_LIBRGA=true \
	  -DLIBRGA_FILE_LIB=${LIBRGA_PATH} \
      -DCMAKE_INSTALL_PREFIX=install \
	..

make
make install

popd
