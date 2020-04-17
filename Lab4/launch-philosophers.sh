#!/usr/bin/env bash
#launch-philosophers - a program that simulates a solution to the
#dining philosopher problem.

#variables
EXEC=dining-p
SEATS=$1

#for all seats, create a philosopher
for ((i=0; $i<$SEATS; $i++))
do

	./$EXEC $SEATS $i
	echo "SEAT: $SEATS , POS: $POS"
done
