#!/bin/bash

set -e

cd /src/cc/
if [ -d "./build" ]; then
    rm -rf ./build
fi

mkdir ./build
cd ./build

if [ $CC_WITHOUT_BUILD -eq 0 ]; then
    cmake .. -DDATABASE=pgsql
    make install
fi
