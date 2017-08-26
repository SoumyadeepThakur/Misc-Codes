#!/bin/sh
FILE=$1
if [ -f $FILE ]
then
    COUNT=`wc -l < "$FILE"`
    echo "No of line in $FILE : $COUNT"
else
    echo "Error: No such file"
fi
