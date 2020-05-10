CFLAGS = -Og
CC = gcc

all: show-bytes32 show-bytes64 sb64-15213.txt

show-bytes32: show-bytes.c
	$(CC) $(CFLAGS) -m32 show-bytes.c -o show-bytes32

show-bytes64: show-bytes.c
	$(CC) $(CFLAGS) -m64 show-bytes.c -o show-bytes64

sb64-15213.txt: show-bytes64
	./show-bytes64 15213 > sb64-15213.txt

clean:
	rm -f *~ *.o show-bytes32 show-bytes64 sb64-15213.txt
