#!/bin/sh

STR="This is my program"
ARGS=$#
TOT=0
COUNT=0
while [ $ARGS -ne 0 ]
do
	FILE=$1
	echo
	echo "In file $FILE"
	echo "-------------------------------------------------------------"
	echo "Line numbers where \"$STR\" occur:"
	grep -n "$STR" $FILE
	COUNT=`grep -c "$STR" $FILE`
	echo	
	echo "\"$STR\" occurs $COUNT times"
	TOT=`expr $TOT + $COUNT`
	ARGS=`expr $ARGS - 1`
	shift
done
echo
echo "Total no of occurences: $TOT"

