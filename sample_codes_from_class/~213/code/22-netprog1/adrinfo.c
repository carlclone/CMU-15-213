#include "csapp.h"
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char **argv) 
{
    if (argc != 2) {
	fprintf(stderr, "usage: %s <ipv4 address>\n", argv[0]);
	exit(0);
    }

    // we will put code to go from a.b.c.d to domain name here

    struct sockaddr_in ipv4addr;
    struct sockaddr *addr = (struct sockaddr *)&ipv4addr;

    memset(addr, 0, sizeof(struct sockaddr_in));
    ipv4addr.sin_family = AF_INET;
    if (inet_aton(argv[1], &(ipv4addr.sin_addr)) == 0) {
      fprintf(stderr, "%s is not a valid ipv4 address\n", argv[1]);
      exit(-1);
    }

    const int HOSTLEN = 256;
    char host[HOSTLEN];
    Getnameinfo(addr, sizeof(struct sockaddr_in),
		host, HOSTLEN,
		NULL, 0,
		NI_NOFQDN);
    printf("%s\n", host);
    exit(0);
}

