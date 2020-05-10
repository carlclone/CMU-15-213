CC = gcc

CFLAGS = -O0 -Wall -g
LDLIBS = -lpthread -lrt

PROGS =	read-write \
	read-write2 \
	rwqueue-test \
	deadlock \
	signaldeadlock \
	signal-sprintf-nodeadlock \


all: $(PROGS)
	pushd pthreads_interpose; make; popd

# Dependencies
produce-consume: produce-consume.c csapp.h csapp.c sbuf.h sbuf.c
read-write: read-write.c csapp.h csapp.c
read-write2: read-write2.c csapp.h csapp.c
rwqueue-test: rwqueue-test.c rwqueue.c rwqueue.h csapp.h csapp.c
deadlock: deadlock.c csapp.h csapp.c
signalddeadlock: signaldeadlock.c csapp.h csapp.c


clean:
	rm -f $(PROGS) *.o *.so *~
	pushd pthreads_interpose; make clean; popd
