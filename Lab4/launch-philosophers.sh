#!/usr/bin/env bash
#launch-philosophers - a program that simulates a solution to the
#dining philosopher problem.

#variables
EXEC=dining-p
SEATS=$1
child=$!
pids=()

#signal handler, terminate all children
sig_handler(){
#kill all children
	for((i=0; $i<$SEATS; i+=1))
	do
		kill -TERM ${pids[i]} 2>/dev/null
	done

#return success from the parent process
	exit 0
}

#catch SIGTERM
trap 'sig_handler' TERM

#each child models a particular philosopher
#for all seats (N), create a philosopher
for ((i=0; $i<$SEATS; i+=1))
do

#forking dining-p -> &
#wait for all children -> ()
	./$EXEC $SEATS $i &

#get the pids of the children
	pids[${i}]=$!
done
wait
