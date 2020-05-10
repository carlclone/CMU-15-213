/* Copy fropm file to stdout, using mmap to load file */
#include "csapp.h"

int main(int argc, char **argv) 
{
    struct stat stat;
    if (argc != 2) exit(1);
    int infd = Open(argv[1], O_RDONLY, 0);
    Fstat(infd, &stat);
    size_t size = stat.st_size;
    char *bufp = Mmap(NULL, size, PROT_READ, 
		      MAP_PRIVATE, infd, 0);
    Write(1, bufp, size);
    exit(0);
}


