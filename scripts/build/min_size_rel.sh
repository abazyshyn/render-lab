#! /bin/bash

cmake . -G Ninja
bear -- ninja -DCMAKE_BUILD_TYPE=MinSizeRel

