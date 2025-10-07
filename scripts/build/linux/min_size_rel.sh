#! /bin/bash

cmake . -G Ninja -DCMAKE_BUILD_TYPE=MinSizeRel
ninja --verbose 

