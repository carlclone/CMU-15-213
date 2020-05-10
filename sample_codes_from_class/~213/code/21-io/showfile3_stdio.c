/* Copy from file to stdout, using rio */
#include "csapp.h"

#define MLINE 1024

int main(int argc, char **argv) 
{
    char buf[MLINE];
    FILE *infile = stdin;
    if (argc == 2) {
	infile = fopen(argv[1], "r");
	if (!infile) exit(1);
    }
    while(fgets(buf, MLINE, infile) != NULL)
	fprintf(stdout, buf);
    exit(0);
}




