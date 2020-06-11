cmake_minimum_required(VERSION 3.13)
project(00_c_programming_lab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(traces)

add_executable(00_c_programming_lab
    traces/trace-01-ops.cmd
    traces/trace-02-ops.cmd
    traces/trace-03-ops.cmd
    traces/trace-04-ops.cmd
    traces/trace-05-ops.cmd
    traces/trace-06-string.cmd
    traces/trace-07-robust.cmd
    traces/trace-08-robust.cmd
    traces/trace-09-robust.cmd
    traces/trace-10-malloc.cmd
    traces/trace-11-malloc.cmd
    traces/trace-12-malloc.cmd
    traces/trace-13-perf.cmd
    traces/trace-14-perf.cmd
    traces/trace-15-perf.cmd
    traces/trace-eg.cmd
    console.c
    console.h
    driver.py
    harness.c
    harness.h
    Makefile
    qtest.c
    queue.c
    queue.h
    README
    README.pdf
    report.c
    report.h)
