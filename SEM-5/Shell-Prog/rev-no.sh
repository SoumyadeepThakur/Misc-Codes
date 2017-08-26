#!/bin/sh
NUM=$1
REV=0
MOD=0
while [ "$NUM" -gt "0" ]
do
    MOD=$(( NUM % 10))
    REV=$(( MOD + REV * 10))
    NUM=$(( NUM / 10 ))
done
echo $REV
