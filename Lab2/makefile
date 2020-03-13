# Name: Priya Singh
# Project: Lab 1: Time and Forking Children
# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.

# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 

EXECUTABLES = launch tube
SRC_1 = launch.c
FILE_1 = launch
OBJ_1 = launch.o

SRC_2 = tube.c
FILE_2 = tube
OBJ_2 = tube.o

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
	$(CC) $(CFLAGS) -c $(SRC_1) -Wall -Wextra
	$(CC) $(CFLAGS) -o $(FILE_1) $(OBJ_1)

	$(CC) $(CFLAGS) -c $(SRC_2) -Wall -Wextra
	$(CC) $(CFLAGS) -o $(FILE_2) $(OBJ_2)

# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.

clean:
	rm -f $(EXECUTABLES) $(OBJ_1) *~
	rm -f $(EXECUTABLES) $(OBJ_2) *~
