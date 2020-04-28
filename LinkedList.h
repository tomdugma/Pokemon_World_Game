#ifndef _LIST
#define _LIST
#include "Defs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_t* list;
typedef struct node_t* l_node;



typedef enum {
    LIST_BAD_ARGUMENT,
    LIST_SUCCESS, LIST_FAIL, LIST_EMPTY
} ListResult;

list createLinkedList(copyFunction cpfunc, freeFunction frfunc, printFunction prtfunc,equalFunction compareelements);

ListResult destroyList(list l);

ListResult list_prepend(list l, element elem);

void appendNode(list l, element elem);

ListResult deleteNode(list l, element elem);

l_node get_head(list l);

l_node get_tail(list l);

l_node get_next(l_node node);

element get_elem(l_node node);

int list_size(list l);

void displayList(list l);

element searchByKeyInList(list l, element elem);

#endif

/* Function that can iterate over list
typedef element(*ListIterator)(element*);

void list_for_each(list list, ListIterator iterator);
*/
