#!/bin/sh
echo "Testing the pthread_cond_wait() wrapper implementation"
LD_PRELOAD="./pthreads_wrapper.so" ./test_cond_wait
