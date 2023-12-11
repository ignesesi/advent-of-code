#!/bin/bash
set -e
if [[ $# -eq 0 ]] ; then
    echo "No arguments provided"
    exit -1
fi

day=$1

cp ${day}/part1.cpp ${day}/part2.cpp
cp ${day}/part1.in ${day}/part2.in
cp ${day}/test1.in ${day}/test2.in

