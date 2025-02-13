#!/bin/bash

Run(){
    pushd build/ > /dev/null
    cmake ..
    make 
    ./scratch_engine2
    popd > /dev/null
}

RunDebug(){
    pushd build/ > /dev/null
    cmake ..
    make 
    lldb ./scratch_engine2
    popd > /dev/null
}

case $1 in 
    debug  ) RunDebug   ;;
    *      ) Run        ;;
esac
