#!/bin/sh
#function
is_prime()
{
	NUMBER=$NUM
	i=2
	while [ $i -lt $NUMBER ]
	do
		if [ `expr $NUMBER % $i` -eq 0 ]
		then
			echo "$NUMBER is not prime"
			exit
		fi
		i=`expr $i + 1`
	done
	echo "$NUMBER is prime"
	
			
}
#main program
echo "Enter number: "
read NUM
is_prime $NUM
