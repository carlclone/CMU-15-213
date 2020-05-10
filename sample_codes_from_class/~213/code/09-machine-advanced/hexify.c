/* Convert sequence of hex digits on stdin into a string, terminated by '\n' */

#include <stdio.h>

int main(int argc, char *argv[]) {
    int hdig;
    while(scanf("%x", &hdig) == 1) {
	putchar(hdig);
    }
    putchar('\n');
    return 0;
}
