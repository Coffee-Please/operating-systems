# Name: Priya Singh
# Project: Lab 4 | Rice, Rice, and Rice
# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.

# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 

EXECUTABLES = dining-p launch-philosophers

FILE_1 = dining-p
SRC_1 = dining-p.c
OBJ_1 = dining-p.o

SRC_2 = launch-philosophers.sh

LIBS = -lpthread -lrt

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set

CC = gcc
CFLAGS = -g


# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables

all: $(EXECUTABLES)


# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.

$(EXECUTABLES):


#Here is the launch-philosophers target for the Makefile.
#
launch-philosophers:
	chmod +x $(SRC_2)


#Here is the dining-p target for the Makefile.
#

dining-p:
	$(CC) $(CFLAGS) -c $(SRC_1) ${LIBS} -Wall -Wextra
	$(CC) $(CFLAGS) -o $(FILE_1) $(OBJ_1) ${LIBS}


# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.

clean:
	rm -f $(EXECUTABLES) $(OBJ_1) *~
