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

void q_insert_first(queue_t *q, list_ele_t *pEle) {
    if (q == NULL) {
        return;
    }
    q->head = pEle;
    q->tail = pEle;
    q->size++;
}


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
    if (q == NULL) { return false; }

    list_ele_t *new_header;
    /* What should you do if the q is NULL? */
    new_header = malloc(sizeof(list_ele_t));
    if (new_header == NULL) { return false; }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */

    //复制字符串
    char *dst = copy_string(s);
    if (dst == NULL) {
        free(new_header);
        return false;
    }
    //如果没有一个元素
    if (q->head == NULL) {
        q_insert_first(q, new_header);
    } else {
        //否则插入头部,修改 head 指针
        new_header->next = q->head;
        q->head = new_header;
    }

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


char *copy_string(char *s) {
    unsigned int len = strlen(s) + 1;
    char *dst = malloc(sizeof(char) * len);
    if (dst == NULL) {
        return NULL;
    }
    strcpy(dst, s);
    dst[len - 1] = '\0';
}

bool q_insert_tail(queue_t *q, char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return false;
    }

    list_ele_t *ele = malloc(sizeof(list_ele_t));
    if (ele == NULL) {
        return false;
    }
    //分配s 字符串大小的 char 数组 //然后复制
    char *dst = copy_string(s);

    if (dst == NULL) {
        free(ele);
        return false;
    }


    //赋值给 ele->value
    ele->value = dst;

    //如果 q 一个元素也没有
    if (q->head == NULL) {
        q_insert_first(q, ele);
    } else {
        q->tail->next = ele;
        q->tail = q->tail->next;
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
void free_an_ele(list_ele_t *pEle) {
    free(pEle->value);
    free(pEle);
}

bool q_remove_head(queue_t *q, char *sp, size_t bufsize) {
    /* You need to fix up this code. */
    if (q == NULL) {
        return false;
    }
    if (q->head == NULL) {
        return false;
    }

    //sp 不为空,复制被删除的 string
    if (sp) {
        unsigned int len = strlen(q->head->value) + 1;

        strcpy(sp, q->head->value);
        sp[len - 1] = '\0';
    }

    //删除 head 并且 free 掉所有空间
    list_ele_t *remove_head = q->head;
    q->head = q->head->next;
    free_an_ele(remove_head);

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q) {
        return 0;
    }
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

