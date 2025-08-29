#! /bin/bash

cmake . -G Ninja -DCMAKE_BUILD_TYPE=Debug
bear -- ninja --verbose 
