#!/bin/sh
pushd src/ > /dev/null
g++ *.cpp -o ../engine/scratch_engine -lsfml-graphics -lsfml-window -lsfml-system
popd > /dev/null

pushd engine/ > /dev/null
./scratch_engine
popd > /dev/null