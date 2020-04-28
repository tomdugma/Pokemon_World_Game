/*
 * MaxHeap.c
 *
 *  Created on: Dec 11, 2019
 *      Author: ise
 */

#include "MaxHeap.h"

struct heap_t {
    char* name;
    int maxSize;
    int count;
    element *array;
    copyFunction copyelement;
    freeFunction freeelement;
    compareFunction compareelements;
    printFunction printelement;

};

heap CreateHeap(char *heapName, int maxSize, copyFunction cpfunc,
                freeFunction frfunc, compareFunction cmpfunc, printFunction prtfunc) {
    if (maxSize < 0)
        return NULL;

    heap h = (heap) malloc(sizeof(struct heap_t));
    if (h == NULL)
        return NULL;

    h->name = (char*) malloc(strlen(heapName) * sizeof(char) + 1);
    if (h->name == NULL) {
        free(h);
        return NULL;
    }
    strcpy(h->name, heapName);

    h->maxSize = maxSize;
    h->count = 0;

    h->array = (element*) malloc(sizeof(element) * maxSize);
    if (h->array == NULL) {
        free(h->name);
        free(h);
        return NULL;
    }
    for(int i = 0;i < h->maxSize ;i++)
    {
		h->array[i] = NULL;
    }

    h->copyelement = cpfunc;
    h->freeelement = frfunc;
    h->compareelements = cmpfunc;
    h->printelement = prtfunc;

    return h;

}

void destroyHeap(element h) {
    if (h == NULL)
        return;

    heap thisHeap = (heap)h;

    while (thisHeap->count > 0) {
        thisHeap->freeelement(thisHeap->array[thisHeap->count - 1]);
        thisHeap->count--;
    }
    free(thisHeap->array);
    free(thisHeap->name);
    free(thisHeap);
    return;

}

HeapResult insertToHeap(heap h, element elem) {
    if ((h == NULL) || (h->maxSize < 0))
        return HEAP_BAD_ARGUMENT;

    if (NULL==elem)
        return HEAP_FAIL;

    if (h->count == h->maxSize)
        return HEAP_FULL;

    element copyelem = NULL;

    copyelem = h->copyelement(elem);

    if(copyelem == NULL)
    	return HEAP_FAIL;

    h->array[h->count] = copyelem;
    h->count++;
    if(h->count > 1)
        HeapIncreaseKey(h, copyelem);

    return HEAP_SUCCESS;
}

void HeapIncreaseKey(heap h, element elem) {
    if (h == NULL || elem == NULL)
        return;

    int i = h->count - 1;
    element temp;
    while (i > 0 && h->compareelements(h->array[(i - 1) / 2], h->array[i])
                    == -1) {
        temp = h->array[i];
        h->array[i] = h->array[(i - 1) / 2];
        h->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

HeapResult BuildMaxHeap(heap h) {
    if (h == NULL)
        return HEAP_BAD_ARGUMENT;
    int size = h->count;
    for (int i = (size / 2); i >= 0; i--) {
        max_heapify(h, i, h->count);
    }
    return HEAP_SUCCESS;
}

void max_heapify(heap h, int loc, int count) {
    int left, right, largest;
    element temp;
    left = (2 * loc) + 1;
    right = (2 * loc) + 2;

    if ((left < count) && (h->compareelements(h->array[left], h->array[loc])
                           == 1)) {
        largest = left;
    } else {
        largest = loc;
    }
    if ((right < count) && (h->compareelements(h->array[right],
                                               h->array[largest]) == 1)) {
        largest = right;
    }

    if (largest != loc) {
        temp = h->array[loc];
        h->array[loc] = h->array[largest];
        h->array[largest] = temp;
        max_heapify(h, largest, count);
    }

}

element PopMaxHeap(heap h) {
    if ((h == NULL) || (h->count == 0))
        return NULL;

    element max = h->array[0];
    h->array[0] = h->array[h->count - 1];
    h->count--;
    max_heapify(h, 0, h->count);
    return max;
}

element TopMaxHeap(heap h) {
    if ((h == NULL) || (h->count == 0))
        return NULL;
    return h->array[0];
}

void printHeap(element h1) {
    if (h1 == NULL)
        return;

    heap castedHeap = (heap)h1;

    printf("%s:\n", castedHeap->name);
    if (castedHeap->count == 0) {
        printf("No elements.\n\n");
        return;
    }
    element array[castedHeap->count];
    int i = 1;
    int oldSize = castedHeap->count - 1;
    int count = oldSize + 1;
    while (oldSize >= 0) {
        array[i - 1] = PopMaxHeap(castedHeap);
        printf("%d. ", i);
        castedHeap->printelement(array[i - 1]);
        oldSize--;
        i++;
    }

    for (int j = 0; j < count; j++)
    {
        insertToHeap(castedHeap, array[j]);
        castedHeap->freeelement(array[j]);
    }

    return;
}

char* getHeapId(element elem) {
    heap h = (heap)elem;
    return h->name;
}

int getHeapCurrentSize(heap h) {
    return h->count;
}



/*
 * BELOW WILL BE FUNCTIONS THAT OUR LINKED LIST WILL NEED TO USE
 * FROM HERE THE BATTLE CLASS WILL BE ABLE TO SEND IT TO THE LIST.
 */


int equalHeaps(element one, element two )
{
    if(one == NULL || two == NULL)
        return -1;

    heap castedHeapOne = (heap)one;
//    heap castedHeapTwo = (heap)two;
    char* typeNameToSearch = (char*)two;

    int res = strcmp(castedHeapOne->name, typeNameToSearch);
    return res;
}


element deepCopyHeap(element h)
{
    if(NULL == h)
        return NULL;

    heap castedHeap = (heap)h;
    if(castedHeap == NULL)
    	return NULL;
    heap copy = CreateHeap(castedHeap->name, castedHeap->maxSize, castedHeap->copyelement,castedHeap->freeelement,castedHeap->compareelements,castedHeap->printelement);
    if (copy == NULL)
    	return NULL;
    for(int i = 0;i < copy->maxSize ;i++)
    {
		copy->array[i] = NULL;
    }

    for(int i = 0;i < castedHeap->maxSize ;i++)
    {
		insertToHeap(copy, castedHeap->array[i]);
    }
    return (element)copy;

}

