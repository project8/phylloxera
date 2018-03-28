#!/bin/bash

source /setup.sh

export BUILDLOCATION=/build

mkdir -p /phylloxera/my_build
cd /phylloxera/my_build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX:PATH=${BUILDLOCATION} -DCMAKE_SKIP_INSTALL_RPATH:BOOL=True ..
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX:PATH=${BUILDLOCATION} -DCMAKE_SKIP_INSTALL_RPATH:BOOL=True ..
make -j3
make install
pip3 install colorlog==2.10.0
