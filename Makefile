#!/bin/bash

CC=g++
CFLAGS= -ansi -O5 -Wall
LDFLAGS= -ansi -lm -Wall
EXEC=mat_sparse
OBJ=ll_mat.o

mat_sparse : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o *~ $(EXEC)
