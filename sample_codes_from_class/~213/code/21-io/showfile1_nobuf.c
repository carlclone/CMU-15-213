/* Copy from file to stdout one character at a time */
#include "csapp.h"

int main(int argc, char *argv[]) 
{
    char c;
    int infd = STDIN_FILENO;
    if (argc == 2) {
	infd = Open(argv[1], O_RDONLY, 0);
    }
    while(Read(infd, &c, 1) != 0)
	Write(STDOUT_FILENO, &c, 1);
    exit(0);
}
