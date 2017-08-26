#!/bin/sh

STR="This is my program"
REP="This is copied program"
ARGS=$#
while [ $ARGS -ne 0 ]
do
	FILE=$1
	echo
	echo "In file $FILE"
	echo "-------------------------------------------------------------"
	echo "Line numbers where \"$STR\" occur:"
	grep -n "$STR" $FILE
	echo	
	sed -i -e 's/'"$STR"'/'"$REP"'/g' $FILE
	echo "\"$STR\" replaced with \"$REP\" in $FILE" 
	ARGS=`expr $ARGS - 1`
	shift
done
echo

