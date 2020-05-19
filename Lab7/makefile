# Name: Priya Singh
# Project: Lab 7 | Asynchronous Elephant
# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.

# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 

EXECUTABLES = matrix_gen matrix_add

FILE_1 = matrix_gen
SRC_1 = matrix_gen.c
OBJ_1 = matrix_gen.o

FILE_2 = matrix_add
SRC_2 = matrix_add.c
OBJ_2 = matrix_add.o

LIBS = -lrt

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


#Here is the matrix_gen target for the Makefile.
#
matrix_gen:
	$(CC) $(CFLAGS) -c $(SRC_1) -Wall -Wextra
	$(CC) $(CFLAGS) -o $(FILE_1) $(OBJ_1)


#Here is the matrix_add target for the Makefile.
#
matrix_add:
	$(CC) $(CFLAGS) -c $(SRC_2) -Wall -Wextra
	$(CC) $(CFLAGS) -o $(FILE_2) $(OBJ_2) $(LIBS)


# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.

clean:
	rm -f $(EXECUTABLES) $(OBJ_1) $(OBJ_2) *~



