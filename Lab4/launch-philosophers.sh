#!/usr/bin/env bash
#launch-philosophers - a program that simulates a solution to the
#dining philosopher problem.

#variables
EXEC=dining-p
SEATS=$1

#for all seats (N), create a philosopher
for ((i=0; $i<$SEATS; i+=1))
do
	./$EXEC $SEATS $i &
	echo "./$EXEC $SEATS $i"
done
