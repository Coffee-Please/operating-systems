#!/usr/bin/env bash
#launch-philosophers - a program that simulates a solution to the
#dining philosopher problem.

#variables
EXEC=dining-p
SEATS=$1
child=$!
pids=()

#create <seats> processes
#each child models a particular philosopher
#for all seats (N), create a philosopher
for ((i=0; $i<$SEATS; i+=1))
do

#forking dining-p -> &
#wait for all children -> ()
	sh -c 'echo $PPID'
	./$EXEC $SEATS $i &

#get the pids of the children
	pids[${i}]=$!
done

#create a new process group            (see setpgid(2))
#setpgid(pid(), getpgid());

#signal handler, terminate all children
_sig_handler()
{
	echo "SIGTERM script received"

	for((i=0; $i<SEATS; i+=1))
	do
		kill -TERM $pids[i] 2>/dev/null
	done

#return success from the parent process
	exit

}

#catch SIGTERM
trap sig_handler SIGTERM
