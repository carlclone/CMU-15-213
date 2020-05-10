Synchronization examples

csapp.{c,h}    
        CS:APP3e code library

rw1.c:
	Readers/writers code from CS:APP3e

read-write.c:
read-write2.c:
	Demonstration of readers/writers implementations

rwqueue.{c,h}:
	Code for FIFO-based readers/writers implementation

rwqueue-test.c:
	Code to test FIFO-based readers/writers implementation

deadlock.c:
	Demonstration of deadlock possibilities when different threads
	acquire locks in different orders

pthreads_interpose:
	Code for a library that performs runtime interposition on pthreads calls.
	Interposed version insert small, random delays to increase
	variations in concurrent operations.

	Try running:

	env LD_PRELOAD=./pthreads_wrapper.so ./read-write
	env LD_PRELOAD=./pthreads_wrapper.so ./rwqueue-test


