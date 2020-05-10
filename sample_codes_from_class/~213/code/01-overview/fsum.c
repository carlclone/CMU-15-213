#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256


int main(int argc, char *argv[]) {
  char prefix[BUFSIZE];
  char next[BUFSIZE];
    int i;
    float sum = 0.0;
    for (i = 1; i < argc; i++) {
	float x = atof(argv[i]);
	sum += x;
	if (i == 1) {
	  sprintf(prefix, "%.4g", x);
	} else {
	  sprintf(next, " + %.4g", x);
	  strcat(prefix, next);
	  printf("%s = %.4g\n", prefix, sum);
	}
    }
    return 0;
}

