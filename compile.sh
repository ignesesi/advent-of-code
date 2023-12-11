#!/bin/bash
set -e
if [[ $# -ne 2 ]] ; then
    echo "Two arguments required. Number of day and part."
    exit -1
fi

day=$1
part=$2

cd day${day}

task=part${part}

g++ ${task}.cpp -o ${task}
./${task} test${part}
cat test${part}.out

./${task} part${part}
cat part${part}.out
