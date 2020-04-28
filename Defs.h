#ifndef PokedexDefs
#define PokedexDefs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define Buffersize 300

typedef enum e_bool { false, true } bool;

typedef enum e_status { success, failure, fail_memory } status;

typedef enum e_type_check { me, others } type_check;

typedef void* element;


typedef struct list_t* list;
typedef struct node_t* l_node;
//
typedef element(*copyFunction) (element);
typedef void (*freeFunction) (element);
typedef void (*printFunction) (element);
typedef int(*equalFunction) (element, element);//1 first bigger, 0 - same, -1 second bigger
typedef char*(*getCategoryFunction)(element);
typedef int(*getAttackFunction)(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond); // return the first attack - second attack . also produce the attack of each element.


#endif //PokedexDefs
