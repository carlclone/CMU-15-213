/* Copy from file to stdout using buffer */
#include "csapp.h"

#define BUFSIZE 64

int main(int argc, char *argv[]) 
{
    char buf[BUFSIZE];
    int infd = STDIN_FILENO;
    ssize_t nread = 0;
    if (argc == 2) {
	infd = Open(argv[1], O_RDONLY, 0);
    }
    while((nread = Read(infd, buf, BUFSIZE)) != 0) 
	Write(STDOUT_FILENO, buf, nread);
    exit(0);
}
