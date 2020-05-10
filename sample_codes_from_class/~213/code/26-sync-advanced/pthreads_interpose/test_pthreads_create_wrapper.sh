#!/usr/bin/sh
echo "Testing the pthread_create wrapper implementation"
LD_PRELOAD="./pthreads_wrapper.so" ./test_pthread_create
