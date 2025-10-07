#! /bin/bash

cmake . -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo
ninja --verbose
