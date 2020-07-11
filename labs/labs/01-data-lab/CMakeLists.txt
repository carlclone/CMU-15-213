cmake_minimum_required(VERSION 3.16)
project(01_data_lab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(01_data_lab
    bits.c
    bits.h
    btest.c
    btest.h
    decl.c
    dlc
    driver.pl
    Driverhdrs.pm
    Driverlib.pm
    fshow.c
    ishow.c
    Makefile
    README
    README-datalab
    README.pdf
    tests.c)
