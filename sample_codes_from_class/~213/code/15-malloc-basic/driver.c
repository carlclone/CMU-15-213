/* Simple driver for sample package */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "mm.h"

/* Total heap size */
#define HEAP_SIZE (1 << 12)
//* The heap.  Use aligned attribute to assure double-word alignment */
unsigned char heap[HEAP_SIZE] __attribute__ ((aligned(16)));

/* Array of returned addresses */
#define MAX_ADDR 128
void *allocated[MAX_ADDR];
int alloc_count = 0;

/* Input Line */
#define BUF_SIZE 512

FILE *infile = NULL;

/* Line of the form
   a BYTES    allocate bytes.  Return allocation number
   f NUM      free allocation numbered NUM
   s          show heap status
   h          show help information
   #          Comment
*/

/* Remove trailing newline character from string */
static void trim(char *s) {
    if (s[strlen(s)-1] == '\n')
        s[strlen(s)-1] = 0;
}

static bool process_line(char *line) {
    size_t size;
    int num;
    void *addr;
    char cmd = line[0];
    switch(cmd) {
    case 'h':
        printf("Commands:\n");
        printf("#           Comment line\n");
        printf("h           Show this message\n");
        printf("a COUNT     Allocate space for COUNT bytes\n");
        printf("f NUM       Free allocation numbered #NUM\n");
        printf("s           Show heap status\n");
        printf("i FILE      Read commands from FILE\n");
        printf("q           Exit\n");
        break;
    case 'a':
        if (sscanf(line+2, "%zd", &size) != 1) {
            printf("Couldn't find size in line '%s'\n", line);
            return false;
        }
        addr = mm_malloc(size);
        allocated[alloc_count++] = addr;
        printf("Allocation #%d.  malloc(%zd) --> %p\n", alloc_count, size, addr);
        break;
    case 'f':
        if (sscanf(line+2, "%d", &num) != 1) {
            printf("Couldn't find allocation number in line '%s'\n", line);
            break;
        }
        if (num < 1 || num > alloc_count) {
            printf("Invalid allocation number %d in line '%s '\n", num, line);
            break;
        }
        addr = allocated[num-1];
        if (addr == NULL) {
            printf("Allocation number %d has already been freed\n", num);
            break;
        }
        mm_free(addr);
        allocated[num-1] = NULL;
        printf("free(%p)\n", addr);
        break;
    case 'i':
        infile = fopen(line+2, "r");
        if (!infile)
            printf("Couldn't open file '%s'\n", line+2);
        break;
    case 's':
        mm_status(stdout);
        break;
    case '#':
        break;
    case 'q':
        return false;
    default:
        printf("Unknown command '%c'\n", cmd);
    }
    return true;
}

int main(int argc, char *argv[]) {
    char line_buf[BUF_SIZE];
    mm_init(heap, HEAP_SIZE);
    infile = stdin;
    while (true) {
        fputs("cmd>", stdout);
        fflush(stdout);
        if (fgets(line_buf, BUF_SIZE, infile) == 0)
            break;
        if (infile != stdin)
            printf("%s", line_buf);
        trim(line_buf);
        if (!process_line(line_buf))
            break;
    }
    return 0;
}
