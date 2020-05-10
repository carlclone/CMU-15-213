This directory contains the code for an implicit-list allocator.  It
uses a footer on every block to enable coalescing.

Files:

mm.h, mm-reference.c
      Allocator implementation

driver.c
      Command-line interpreter for testing allocator

memops.cmd
      File containing sequence commands for a test

Compile with "make".  It generates a program mm-reference

Usage:

Type './mm-reference'.  You will be in a command-line interpreter.
Type 'h' to see a list of commands
Type 'i memops.cmd' to run the provided test sequence




