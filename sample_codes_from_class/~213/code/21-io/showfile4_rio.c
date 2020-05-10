/* Copy from file to stdout, using rio */
#include "csapp.h"

#define MLINE 1024

int main(int argc, char **argv) 
{
    rio_t rio;
    char buf[MLINE];
    int infd = STDIN_FILENO;
    ssize_t nread = 0;
    if (argc == 2) {
	infd = Open(argv[1], O_RDONLY, 0);
    }
    Rio_readinitb(&rio, infd);
    while((nread = Rio_readlineb(&rio, buf, MLINE)) != 0) 
	Rio_writen(STDOUT_FILENO, buf, nread);
    exit(0);
}




