This directory contains the source code for program sq and struct.
Both demonstrate subtle features of computer programs.

sq: The program prints the squares of each value entered on the command line.

    Try running:

    	./sq 40000

    and

	./sq 50000

struct: References into an array, possibly corrupting a stored double
	or creating a segmentation fault.

    Try running

    	./struct 0
    	./struct 1
    	./struct 2
    	./struct 3
    	./struct 4

fsum: Computes sum of arguments as data type float,
      summing from left to right


    Try running
    	./fsum 1e20 -1e20 3.14
	./fsum 1e20 3.14 -1e20

