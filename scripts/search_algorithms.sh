#!/bin/bash

if [ $# -ne 2 ];
  then
    >&2 echo "Give me the executable path and search int."
    exit 1;
fi

alg_path=$1;
nbr=$2

for g in `seq 1 3`;
do
    for i in `seq 10 10 10000`;
    do
        ${alg_path} ${g} ${i} ${nbr}
    done
done
