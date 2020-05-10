CC = gcc
CFLAGS = -g -O1

FILES = sq struct fsum

all: $(FILES)

sq: sq.c
	$(CC) $(CFLAGS) -o sq sq.c

struct: struct.c
	$(CC) $(CFLAGS) -o struct struct.c

fsum: fsum.c
	$(CC) $(CFLAGS) -o fsum fsum.c

clean:
	rm -f *~ *.o sq struct fsum
	rm -rf *.dSYM

