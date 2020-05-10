Support files for the first synchronization lecture

Makefile
        "make clean; make" to compile everything

badcnt.{c,s}
        C assembly code for the badcnt example

csapp.{c,h}
        CS:APP3e code library

goodcnt.c
        Uses semaphore to fix race in badcnt

goodmcnt.c
        Uses mutex to fix race in badcnt

produce-consume.c:
	Demonstration of producer/consumer code using sbuf

sbuf.{c,h}
	Circular buffer code suitable for producer/consumer programs

sharing.c
        Example program for illustrating how variables are shared by threads

pthreads_interpose:
	Code for a library that performs runtime interposition on pthreads calls.
	Interposed version insert small, random delays to increase
	variations in concurrent operations.

	Try running:

	env LD_PRELOAD=./pthreads_wrapper.so ./produce-consume

qprob/
	Quiz problem code
