#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "csapp.h"
/*
 * This program demonstrates that calling 'sprintf' 
 * from within a signal handler that's invoked asynchronously (like
 * SIGCHLD's is) does NOT appear to cause deadlocks
 * 
 * The program runs to completion with 1,000,000 tests.
 * 
 * Based on program with:
 *
 * @author Godmar Back <godmar@gmail.com>
 * Written for CS 3214 Fall 2009, Virginia Tech
 * 
 * Updated by Dave O'Hallaron to use the sio functions
 * Fall, 2015
 */
#define DEADLOCK 1

#define MAXN 128

static void
catch_child(int signo)
{
    char buf[MAXN];
#if DEADLOCK
    /* this call may reenter printf/puts! Bad! */
    int mypid = (int) getpid();
    int j;
    for (j = 0; j < 10; j++) {
	sprintf(buf, "Child %d %d %d %d exited\n", mypid, mypid, mypid, mypid);
	write(STDOUT_FILENO, buf, strlen(buf));
    }
#else
    /* This version is async-signal-safe */
    sio_puts("Child exitted!\n");
#endif

    /* reap all children */
    while (waitpid(-1, NULL, WNOHANG) > 0)
        continue;
}

int
main()
{
    signal(SIGCHLD, catch_child);

    long i, j;
    for (i = 0; i < 1000000; i++) {
        if (fork() == 0)
            exit(0);

#if DEADLOCK
        puts("Child started\n");
#else
        sio_puts("Child started\n");
#endif

        for (j=0; j<10; j++) {
#if DEADLOCK
            /* Make each printf does a lot of work */
	    char buf[MAXN];
	    sprintf(buf, "%ld %ld %ld %ld %ld %ld %ld %ld\n", i, i, i, i, i, i, i, i);
	    write(STDOUT_FILENO, buf, strlen(buf));
	    //	    puts(buf);
	    //            printf("%ld%ld%ld%ld%ld%ld%ld%ld", i, i, i, i, i, i, i, i);
#else
            sio_emitl("i");
            sio_emitl("i");
            sio_emitl("i");
            sio_emitl("i");
            sio_emitl("i");
            sio_emitl("i");
            sio_emitl("i");
            sio_emitl("i");
#endif
        }
    }
    return 0;
}
