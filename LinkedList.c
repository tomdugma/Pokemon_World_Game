#include "LinkedList.h"

struct node_t {
    element* elem;
    struct node_t* next;
    struct node_t* prev;
};

struct list_t {
    l_node head;
    l_node tail;
    int size;
    copyFunction copyelement;
    freeFunction freeelement;
    equalFunction compareelements;
    printFunction printelement;


};


list createLinkedList(copyFunction cpfunc, freeFunction frfunc,
                      printFunction prtfunc,equalFunction compareelements)
{
    list l = (list) malloc(sizeof(struct list_t));
    if (l == NULL)
        return NULL;
    l->size = 0;
    l->head = l->tail = NULL;
    l->copyelement = cpfunc;
    l->freeelement = frfunc;
    l->compareelements = compareelements;
    l->printelement = prtfunc;
    return l;
}

ListResult destroyList(list l) {
    if (l == NULL)
        return LIST_BAD_ARGUMENT;

    l_node current = l->head;
    l_node temp;
    if (l->size == 1) {
        l->freeelement(current->elem);
        free(current);
        free(l);
        return LIST_SUCCESS;
    }

    do {
        l->freeelement(current->elem);
        temp = current;
        current = current->next;
        free(temp);

    } while (current != NULL);

    free(l);
    return LIST_SUCCESS;
}

ListResult list_prepend(list l, element elem) {
    if (l == NULL || elem == NULL)
        return LIST_BAD_ARGUMENT;

    l_node node = malloc(sizeof(struct node_t));
    if (node == NULL)
        return LIST_FAIL;

    element copyelem;
    copyelem = l->copyelement(elem);

    node->elem = copyelem;

    node->next = l->head;
    node->prev = NULL;
    l->head = node;
    if (node->next) {
        node->next->prev = node;
    }

    // first node?
    if (!l->tail) {
        l->tail = l->head;
    }
    l->size++;
    return LIST_SUCCESS;
}

void appendNode(list l, element elem) {
    if (l == NULL || elem == NULL)
        return;

    l_node node = malloc(sizeof(struct node_t));

    if (node == NULL)
        return;

    element copyelem = NULL;
    copyelem = l->copyelement(elem);

    node->elem = copyelem;
    node->next = NULL;

    if (l->size == 0) {
        node->prev = NULL;
        l->head = l->tail = node;
    } else {
        node->prev = l->tail;
        l->tail->next = node;
        l->tail = node;
    }
    l->size++;
    return;

}

ListResult deleteNode(list l, element elem) {

    if (l == NULL || elem == NULL)
        return LIST_BAD_ARGUMENT;

    l_node current = l->head;
    while (current != NULL) {

        if (l->compareelements(current->elem, elem) == 0) {
            /* Update prev node or list head */
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                l->head = current->next;
            }

            /* Update next node or list tail */
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                l->tail = current->prev;
            }

            /* Finally free the node */
            if (current->elem) {
                l->freeelement(current->elem);
            }
            free(current);
            l->size--;
            return LIST_SUCCESS;
        } else {
            current = current->next;
        }
    }
    return LIST_FAIL;
}

l_node get_head(list l) {
    return l->head;
}
l_node get_tail(list l) {
    return l->tail;
}
l_node get_next(l_node node) {
    return node->next;
}
element get_elem(l_node node) {
    return node->elem;
}

int list_size(list l) {
    return l->size;
}

void displayList(list l) {

    if (l == NULL)
        return;

    l_node node = l->head;
    while(node != NULL)
    {
        l->printelement(node->elem);
    }

}

element searchByKeyInList(list l, element elem) {
    if (l == NULL || elem == NULL)
        return NULL;

    l_node current = l->head;
    while (current != NULL) {
        if (l->compareelements(current->elem, elem) == 0) {
            return current->elem;
        }
        current = current->next;
    }
    return NULL;
}
