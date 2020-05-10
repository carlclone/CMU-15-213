CC = gcc

CSAPP_INC = .
CSAPP_SRC = .

CFLAGS = -Wall -g -Og -I $(CSAPP_INC) -I .
LDLIBS = -lpthread

PROGS =	statcheck\
	hello\
	ffiles1\
	ffiles2\
	ffiles3\
	showfile1_nobuf\
	showfile2_buf\
	showfile3_stdio\
	showfile4_rio\
	showfile5_mmap\


all: $(CSAPP_SRC)/csapp.o $(PROGS) 
$(PROGS): $(CSAPP_SRC)/csapp.o
$(CSAPP_SRC)/csapp.o: $(CSAPP_SRC)/csapp.c $(CSAPP_INC)/csapp.h

clean:
	rm -f $(PROGS) *.o *~
