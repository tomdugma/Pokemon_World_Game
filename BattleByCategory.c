#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"

struct battle_s{
    int numOfCategories;
    int maxSize;
    int count;
    list listOfBattles;
    equalFunction equalElement;
    copyFunction copyElement;
    freeFunction freeElement;
    getCategoryFunction getCategory;
    getAttackFunction getAttack;
    printFunction printElement;
};



Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,
                              copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement)
{
    if (categories == NULL || equalElement == NULL || copyElement == NULL || freeElement == NULL
        || getCategory == NULL || getAttack == NULL || printElement == NULL) {
        return NULL;
    }
    //equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,
    // getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement

    Battle curBattle = (Battle) malloc(sizeof(struct battle_s));

    if (curBattle == NULL) {
        return NULL;
    }
    curBattle->listOfBattles = NULL;
    curBattle->listOfBattles = createLinkedList(deepCopyHeap, destroyHeap, printHeap, equalHeaps); //copy element NOT TWICE NEED TO FIX
    if(curBattle->listOfBattles == NULL)
    {
    	free(curBattle);
    	return NULL;
    }
    char* typesToSplit;
    typesToSplit = (char*)malloc(sizeof(char)*strlen(categories)+1);
    if (typesToSplit == NULL)
    {
    	free(curBattle);
    	destroyList(curBattle->listOfBattles);
    	return NULL;

    }
    strcpy(typesToSplit,categories);

    //init battle functions
    curBattle ->copyElement = copyElement;
    curBattle->equalElement = equalElement;
    curBattle->freeElement = freeElement;
    curBattle->getAttack = getAttack;
    curBattle->getCategory = getCategory;
    curBattle->printElement = printElement;
    //init battle fields.
    curBattle->numOfCategories = numberOfCategories;
    curBattle->maxSize = capacity;
    curBattle->count = 0;

    int i = 1;
    char *cat = strtok(typesToSplit, ",");
    heap h = NULL;
    h = CreateHeap(cat, curBattle->maxSize, copyElement,freeElement, equalElement, printElement);
    if (h != NULL) {
    	appendNode(curBattle->listOfBattles,h);
    	curBattle->count = curBattle->count + getHeapCurrentSize(h);
    }
    destroyHeap(h);

    while (i < curBattle->numOfCategories){
        if (i == curBattle->numOfCategories-1)
            cat = strtok(NULL, "\n");
        else
            cat = strtok(NULL, ",");
        heap heapTemp = NULL;
        heapTemp = CreateHeap(cat, curBattle->maxSize, copyElement,freeElement, equalElement,printElement);
        if (heapTemp != NULL)
        {
        	appendNode(curBattle->listOfBattles,heapTemp);
        	curBattle->count = curBattle->count + getHeapCurrentSize(heapTemp);
        }
        destroyHeap(heapTemp);
        i++;
    }
    free(typesToSplit);
    return curBattle;

}

status destroyBattleByCategory(Battle b)
{
    if(b == NULL)
        return failure;

    destroyList(b->listOfBattles);
    free(b);
    return success;
}
//elem is actually Pokemon !
status insertObject(Battle b, element elem)
{
    if(b == NULL || elem == NULL)
        return failure;
//    char* typeOfHeap = getHeapId(elem);
    char* cat = b->getCategory(elem);
    heap maxHeap = searchByKeyInList(b->listOfBattles, cat);

    if(maxHeap == NULL)
        return failure;

    if(getHeapCurrentSize(maxHeap) >= b->maxSize)
        return failure;

    else
    {
        insertToHeap(maxHeap, elem);
        b->count++;
    }
    return success;
}

void displayObjectsByCategories(Battle b)
{
    if(b == NULL)
        return;
    l_node node;
    int i = 1;
    for(node = get_head(b->listOfBattles);node != NULL;node=get_next(node))
    {
        //printf("cat%d\n",i);
        printHeap(get_elem(node));
        i++;
    }
}

element removeMaxByCategory(Battle b, char* category)
{
    if(b == NULL || category == NULL)
        return NULL;
    heap heap_to_del = searchByKeyInList(b->listOfBattles,category);
    element max_element = PopMaxHeap(heap_to_del);
    if (max_element != NULL)
    	b->count--;
    return max_element;

}

int getNumberOfObjectsInCategory(Battle b,char* category)
{
    if(b == NULL || category == NULL)
        return -1;

    element elem = searchByKeyInList(b->listOfBattles, category);
    return getHeapCurrentSize(elem);
}

element fight(Battle b,element elem)
{

    if(b == NULL || elem == NULL)
        return NULL;

    if (b->count == 0)
    {
    	printf("There are no Pokemons to fight against you.\n");
    	return NULL;
    }

    //if there is no categories at all.

    if(list_size(b->listOfBattles) <= 0)
        return NULL;
    int* attackA = (int*)malloc(sizeof(int));
    int* attackB = (int*)malloc(sizeof(int));
    int currHighestAttack = 0;
    int check = 0;
    l_node node = get_head(b->listOfBattles);

    element StrongestToFightWith;
    element currStrongestPokemon = TopMaxHeap(get_elem(node));
    currHighestAttack = b->getAttack(currStrongestPokemon, elem, attackA, attackB);
    check = currHighestAttack;
    StrongestToFightWith = currStrongestPokemon;
    while (node != NULL)
    {
        node = get_next(node);
        if (node == NULL)
        	break;
        currStrongestPokemon = TopMaxHeap(get_elem(node));
        check = b->getAttack(currStrongestPokemon,elem,attackA,attackB);
        if(check != -9999 && check > currHighestAttack)
        {
            StrongestToFightWith = currStrongestPokemon;
            currHighestAttack = check;
        }
        else
        	check = b->getAttack(StrongestToFightWith,elem,attackA,attackB);

    }
    printf("The final battle between:\n");
    b->printElement(elem);
    printf("In this battle his attack is :%d\n\n", *attackB);
    printf("against ");
    b->printElement(StrongestToFightWith);
    printf("\n");
    printf("In this battle his attack is :%d\n\n", *attackA);
    if(currHighestAttack > 0)
    {
        printf("THE WINNER IS:\n");
        b->printElement(StrongestToFightWith);
    }
    else if(currHighestAttack < 0)
    {
        printf("THE WINNER IS:\n");
        b->printElement(elem);
    }
    else
    {
        printf("IT IS A DRAW.\n");
    }
    free (attackA);
    free (attackB);

    return NULL;
}



