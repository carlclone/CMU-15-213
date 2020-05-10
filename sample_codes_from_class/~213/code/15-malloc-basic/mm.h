#include <stdlib.h>
/* Interface to simple malloc package */

void mm_init(void *start, size_t byte_count);
void *mm_malloc(size_t size);
void mm_free(void *ptr);
void mm_status(FILE *fp);
