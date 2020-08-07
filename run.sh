#!/bin/bash

export DISPLAY=localhost:0.0

printf "\-\-\- Running shell script -/-/-/\n"

exepath="./bin"
exe="raycast.exe"

mode="none"

if [ $# -eq 0 ] || [ \( $# -eq 1 \) -a \( $1 = "debug" -o $1 = "DEBUG" \) ]; then
    mode="debug"
elif [ \( $# -eq 1 \) -a \( $1 = "release" -o $1 = "RELEASE" \) ]; then
    mode="release"
else
    echo "usage: $0 [release/debug]"
    exit
fi

#export DISPLAY=localhost:0.0

printf "Running $mode mode...\n\n"
if [ $mode = "debug" ]; then
    make && printf "\n--- EXECUTION ---\n\n" && $exepath/debug/$exe
elif [ $mode = "release" ]; then
    make RELEASE=1 && printf "\n--- EXECUTION ---\n\n" && $exepath/release/$exe
fi
