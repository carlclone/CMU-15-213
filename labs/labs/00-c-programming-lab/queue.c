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

/*
 * 模拟的test case
 * pass ......
 *
 *
 */
queue_t *q_new() {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }


    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}

/* Free all storage used by queue */

/*
 * note : 如果ele有str , str也要free掉
 * 模拟的test case
 * q为NULL
 *
 * q不为NULL ,
 * 没有head
 * 遍历链表 ,只有一个head , 有str or 没str
 * 遍历链表,有2个元素,一个有str一个没str
 * pass
 *
 */
void q_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) { return; }

    //遍历队列free
    list_ele_t *my_pointer = q->head;
    while (my_pointer != NULL) {
        list_ele_t *next_point = my_pointer->next;
        if (my_pointer->value != NULL) {
            free(my_pointer->value);
        }
        free(my_pointer);
        my_pointer = next_point;
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */

/*
 * 模拟的test case
 * q为NULL
 * q不为NULL , head为NULL
 *            head不为NULL
 *
 *
 * malloc失败,前面已分配的malloc需要free掉
 *
 * pass..
 *
 */
bool q_insert_head(queue_t *q, char *s) {
    if (q == NULL) {return false;}

    list_ele_t *new_header;
    /* What should you do if the q is NULL? */
    new_header = malloc(sizeof(list_ele_t));
    if (new_header == NULL) {return false;}
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    new_header->next = q->head;

    char *str = malloc(sizeof(char));
    if (str == NULL) {
        free(new_header);
        return false;
    }
    strcpy(str,s);
    new_header->value = str;
    q->head = new_header;

    return true;
}



/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */

/*
 *   head -> ele -> ele -> null
 *
 *   模拟的case
 *
 *
 */
bool q_insert_tail(queue_t *q, char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *ele = malloc(sizeof(list_ele_t));
    if (ele == NULL) {
        return false;
    }
    ele->value = s;

    q->tail->next = ele;
    q->tail = ele;

    return false;
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
    /* You need to fix up this code. */
    q->head = q->head->next;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
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
}

