#!/bin/bash

# if any mode is precised, then release is the default one
mode="release"
# project folder's name is the default application's name
pgname=${PWD##*/}

# release / debug mode / program name
if [ $# -eq 1 ]; then
    if [ $1 = "-d" ]; then
        mode="debug"
    elif [ $1 = "-r" ]; then
        mode="release"
    else
        pgname=$1
    fi
elif [ $# -eq 2 ]; then
    if [ $1 = "-d" ]; then
        mode="debug"
    elif [ $1 = "-r" ]; then
        mode="release"
    else
        echo "Undefined mode given : $1"
        exit 1
    fi
    pgname=$2
fi

# detect os and adapt executable extension
if [ "$OSTYPE" == "darwin"* ]; then # mac OS
    pgname=$pgname.app
elif [ "$OSTYPE" == "cygwin" -o "$OSTYPE" == "msys" -o "$OSTYPE" == "win32" ]; then # windows
    pgname=$pgname.exe
fi

# compile and execute if succeed
make ${mode^^}=1 PGNAME=$pgname && ./bin/$mode/$pgname