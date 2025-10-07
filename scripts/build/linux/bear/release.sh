#! /bin/bash

cmake . -G Ninja -DCMAKE_BUILD_TYPE=Release
bear -- ninja --verbose 

