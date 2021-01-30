#!/bin/bash

# if any mode is precised, then release is the default one
mode="release"
# project folder's name is the default application's name
pgname=${PWD##*/}

# release / debug mode / program name
if [ $# -gt 0 ] && [ $1 == "-d" -o $1 == "-r" ]; then
    [[ $1 == "-d" ]] && mode="debug" || mode="release"
    shift
fi

# detect os and adapt executable extension
if [ "$OSTYPE" == "darwin"* ]; then # mac OS
    pgname=$pgname.app
elif [ "$OSTYPE" == "cygwin" -o "$OSTYPE" == "msys" -o "$OSTYPE" == "win32" ]; then # windows
    pgname=$pgname.exe
fi

# compile and execute if succeed
make ${mode^^}=1 PGNAME=$pgname && printf "\n-----\n\n" && ./bin/$mode/$pgname $@