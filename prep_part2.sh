#!/bin/bash
set -e
if [[ $# -eq 0 ]] ; then
    echo "No arguments provided"
    exit -1
fi

day=$1

cd ${day}

cp part1.cpp part2.cpp
cp part1.in part2.in
cp test1.in test2.in

