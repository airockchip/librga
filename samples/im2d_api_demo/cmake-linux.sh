#!/bin/bash

SCRIPT_DIR=$(cd $(dirname ${BASH_SOURCE[0]}); pwd)
BUILD_DIR=build_linux
BINARY_DIR=$BUILD_DIR/bin
LIBRGA_PATH=${SCRIPT_DIR}/../../libs

rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR
mkdir -p $BINARY_DIR
pushd $BUILD_DIR

if [ "$1" = "drm" ];then
	echo "using drm"
	cmake -DCMAKE_BUILD_TARGET=buildroot \
		  -DBUILD_TOOlCHAINS_PATH=../../buildroot.cmake \
		  -DBUILD_WITH_LIBDRM=true \
		  -DBUILD_WITH_LIBRGA=true \
		  -DLIBRGA_FILE_LIB=${LIBRGA_PATH} \
		  -DCMAKE_INSTALL_PREFIX=install \
		  ..
else
	echo "Default mode $1"
	cmake -DCMAKE_BUILD_TARGET=buildroot \
		  -DBUILD_TOOlCHAINS_PATH=../../buildroot.cmake \
		  -DBUILD_WITH_LIBRGA=true \
		  -DLIBRGA_FILE_LIB=${LIBRGA_PATH} \
		  -DCMAKE_INSTALL_PREFIX=install \
		  ..
fi

make
make install

popd

