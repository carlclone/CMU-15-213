/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new() {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q != NULL) { /* If q not NULL, do initialization.*/
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q) {
    if (q != NULL) {
        /* How about freeing the list elements and the strings? */
        /* Free queue structure */
        list_ele_t *curr = q->head;
        list_ele_t *want_free = NULL;
        while (curr) { /* Check whether current pointed Linked list element struct is NULL.*/
            want_free = curr; /* If yes, free it.*/
            curr = curr->next; /* Point to next struct */
            free(want_free->value);
            free(want_free);
        }
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s) {
    /* What should you do if the q is NULL? */
    if (q == NULL) return false;
    /* Initialize memory allocation for new head.*/
    list_ele_t *new_head;
    new_head = malloc(sizeof(list_ele_t));
    if (new_head == NULL) return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    new_head->value = malloc((strlen(s) + 1) * sizeof(char));
    if (new_head->value == NULL) {
        free(new_head);
        return false;
    }
    strcpy(new_head->value, s);
    new_head->next = q->head;
    q->head = new_head;
    q->size++;
    if (q->size == 1) q->tail = new_head;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s) {
    if (q == NULL) return false;
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *new_tail;
    new_tail = malloc(sizeof(list_ele_t));
    if (new_tail == NULL) return false;

    new_tail->value = malloc((strlen(s) + 1) * sizeof(char));
    if (new_tail->value == NULL) {
        free(new_tail);
        return false;
    }
    strcpy(new_tail->value, s);
    new_tail->next = NULL;
    q->size++;
    /* If only one element, point head and tail to same struct.*/
    if (q->size <=1) {
        q->head = new_tail;
        q->tail = new_tail;
    } else { /* Else, append tail.*/
        q->tail->next = new_tail;
        q->tail = new_tail;
    }
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize) {
    if ((q == NULL) || (q->size == 0)) return false;
    /* You need to fix up this code. */
    list_ele_t *want_free = q->head;
    q->head = q->head->next;
    q->size --;

    if (q->size == 0) {
        q->tail = NULL;
    }
    //Copied to sp
    if(sp != NULL){
        int counter = 0;
        while(*((want_free -> value)+counter) != 0x00 && counter < (int) bufsize-1){
            *(sp+counter) = *((want_free -> value)+counter);
            counter += 1;
        }
        *(sp+counter) = 0x00;
    }
    free(want_free->value);
    free(want_free);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q != NULL) return q->size;
    return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if ((q == NULL) || (q->size == 0)) return;
    list_ele_t *prev = NULL;
    list_ele_t *curr = q->head;
    list_ele_t *next = curr->next;

    q->tail = q->head;

    while (next) { /* If next is NULL stop, if not reverse current point.*/
        curr->next = prev;
        prev = curr;
        curr = next;
        next = curr->next;
    }

    curr->next = prev;
    q->head = curr;
}