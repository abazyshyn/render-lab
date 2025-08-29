#! /bin/bash

cmake . -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo
bear -- ninja --verbose
