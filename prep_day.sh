#!/bin/bash
set -e
if [[ $# -eq 0 ]] ; then
    echo "No arguments provided"
    exit -1
fi

day=$1

mkdir ${day}
cp template.cpp ${day}/part1.cpp

