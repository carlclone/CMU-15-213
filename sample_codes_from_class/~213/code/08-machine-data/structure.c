#include <stdlib.h>

struct rec {
    int a[4];
    size_t i;
    struct rec *next;
};

void set_i(struct rec *r, size_t val)
{
    r->i = val;
}

int *get_ap(struct rec *r, size_t idx)
{
    return &r->a[idx];
}

int check_val(struct rec *r, int val) {
    int found = 0;
    while (!found && r) {
	size_t i = r->i;
	if (r->a[i] == val)
	    found = 1;
	else
	    r = r->next;
    }
    return found;
}

long length(struct rec*r) {
    long len = 0L;
    while (r) {
	len ++;
	r = r->next;
    }
    return len;
}

void set_val(struct rec *r, int val) {
    while (r) {
	size_t i = r->i;
	// Missing bounds check
	r->a[i] = val;
	r = r->next;
    }
}

