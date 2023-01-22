#!/bin/sh
pushd build/ > /dev/null
cmake ..
make .
./scratch_engine2
popd > /dev/null