/*
 * MaxHeap.h
 *
 *  Created on: Dec 11, 2019
 *      Author: ise
 */

#ifndef SRC_MAXHEAP_H_
#define SRC_MAXHEAP_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef void* element;
typedef element (*copyFunction)(element);
typedef void (*freeFunction)(element);
typedef int (*compareFunction)(element, element);
typedef void (*printFunction)(element);
typedef struct heap_t* heap;

typedef enum {HEAP_BAD_ARGUMENT, HEAP_SUCCESS, HEAP_FAIL, HEAP_EMPTY, HEAP_FULL} HeapResult;

heap CreateHeap (char *heapName, int maxSize, copyFunction cpfunc, freeFunction frfunc, compareFunction cmpfunc, printFunction prtfunc);

void max_heapify(heap h, int loc, int count);

void destroyHeap(element h);

HeapResult insertToHeap (heap h, element elem);

void printHeap(element h1);

element PopMaxHeap (heap h);

element TopMaxHeap (heap h);

char* getHeapId(element elem);

int getHeapCurrentSize(heap h);

void swap(element A, element B);

void HeapIncreaseKey(heap h,element elem);

element deepCopyHeap(element h);

int equalHeaps(element one, element two );

HeapResult BuildMaxHeap(heap h);

#endif /* SRC_MAXHEAP_H_ */
