#include "Pokemon.h"
/*
 * Create pokemon function :
 * recieve *type, *det, *name, *species
 * return pointer to Pok object.
 */

Pok* createPokemon(Type* addtype, Det* det, char* name, char* species) {
    if (addtype == NULL || det == NULL || name == NULL || species == NULL)
        return NULL;

    Pok* newPok = (Pok*)malloc(sizeof(Pok));
    if (newPok == NULL) {
        return NULL;
    }

    newPok->name = (char*)malloc(strlen(name) * sizeof(char) + 1);
    if (newPok->name == NULL) {
        free(newPok);
        return NULL;
    }
    strcpy(newPok->name, name);

    newPok->species = (char*)malloc(strlen(species) * sizeof(char) + 1);
    if (newPok->species == NULL) {
        free(newPok);
        free(newPok->name);
        return NULL;
    }
    strcpy(newPok->species, species);
    newPok->Det = det;
    newPok->Type = addtype;
    addtype->size++;

    return newPok;

}

void PokDestroy(element elem)
{
    if (elem == NULL)
        return;

    Pok* pok_to_des = (Pok*)(elem);
    free(pok_to_des->Det);
    free(pok_to_des->name);
    free(pok_to_des->species);
    pok_to_des->Type->size--;
    free(pok_to_des);
    return;

}

/*
 * CreatePokemonType:
 * recieve char *name
 * return pointer to Type Object.
 */

Type* createPokemonType(char* name) {

    if (name == NULL)
        return NULL;
    Type* newType;
    newType = (Type*)malloc(sizeof(Type));
    if (newType == NULL) {
        return NULL;
    }
    newType->typeName = (char*)malloc(strlen(name) * sizeof(char) + 1);
    if (newType->typeName == NULL) {
        free(newType);
        return NULL;
    }
    strcpy(newType->typeName, name);
    newType->sizeOfGood_ag_me = 0;
    newType->good_ag_me = (Type**)malloc(sizeof(Type*));
    if (newType->good_ag_me == NULL) {
        free(newType);
        free(newType->typeName);
        return NULL;
    }
    newType->sizeOfGood_ag_others = 0;
    newType->good_ag_others = (Type**)malloc(sizeof(Type*));
    if (newType->good_ag_others == NULL) {
        free(newType);
        free(newType->typeName);
        free(newType->good_ag_me);
        return NULL;
    }
    newType->size = 0;
    return newType;
}

status TypeDestroy(Type* type_to_des)
{
    if (type_to_des == NULL)
        return failure;

    free(type_to_des->typeName);
    free(type_to_des->good_ag_me);
    free(type_to_des->good_ag_others);
    free(type_to_des);
    return success;

}


/*
 * createPokemonData
 * recieves double height, double weight, int attack
 * returns pointer to Det Object.
 */

Det* createPokemonData(double height, double weight, int attack) {
    Det* data = (Det*)malloc(sizeof(Det));
    if (data == NULL) {
        return NULL;
    }

    data->height = height;
    data->weight = weight;
    data->attack = attack;
    return data;
}

/*
 * add_eff_ag_me func:
 * recieve two pointers, A, B, add B to the list of type A.
 * return status if action succussed or not
 */

status add_effective_ag_me(Type* A, Type* B) {
    if (A == NULL || B == NULL)
        return failure;

    if (A->sizeOfGood_ag_me == 0) {
        A->good_ag_me[0] = B;
        A->sizeOfGood_ag_me++;
    }
    else {
        A->sizeOfGood_ag_me++;
        A->good_ag_me = (Type**)realloc(A->good_ag_me, sizeof(Type*) * A->sizeOfGood_ag_me);

        if (A->good_ag_me == NULL) {
            return failure;
        }
        A->good_ag_me[A->sizeOfGood_ag_me - 1] = B;
    }

    return success;
}

/*
 * add_eff_ag_others func:
 * recieve two pointers, A, B, add B to the list of type A.
 * return status if action succussed or not
 */
status add_effective_ag_others(Type* A, Type* B) {
    if (A == NULL || B == NULL)
        return failure;

    if (A->sizeOfGood_ag_others == 0) {
        A->good_ag_others[0] = B;
        A->sizeOfGood_ag_others++;
    }
    else {
        A->sizeOfGood_ag_others++;
        A->good_ag_others = (Type**)realloc(A->good_ag_others,
                                            sizeof(Type*) * A->sizeOfGood_ag_others);
        if (A->good_ag_others == NULL) {
            return failure;
        }
        A->good_ag_others[A->sizeOfGood_ag_others - 1] = B;

    }
    return success;
}


/*
 * delete from eff ag me func:
 * recieve pointer to type A, and char of type B, delete type B from A list if B exists there.
 * return status if action succussed or not
 */
status delete_from_effective_ag_me(Type* A, char* B) {
    if (A == NULL || B == NULL)
        return failure;

    if ((A->sizeOfGood_ag_me == 1) && (strcmp(A->good_ag_me[0]->typeName, B) == 0)) {
        A->sizeOfGood_ag_me = 0;
    }
    else {
        for (int i = 0; i < A->sizeOfGood_ag_me; i++) {
            if (strcmp(A->good_ag_me[i]->typeName, B) == 0) {
                int j = i;
                for (; j < A->sizeOfGood_ag_me - 1; j++) {
                    A->good_ag_me[j] = A->good_ag_me[j + 1];
                }
                A->sizeOfGood_ag_me--;
                return success;
            }
        }
        return failure;
    }
    if (A->sizeOfGood_ag_me == 0) {
        A->good_ag_me[0] = NULL;
        return success;
    }
    return failure;
}

/*
 * delete from eff ag others func:
 * recieve pointer to type A, and char of type B, delete type B from A list if B exists there.
 * return status if action succussed or not
 */

status delete_from_effective_ag_others(Type* A, char* B) {
    if (A == NULL || B == NULL)
        return failure;

    if ((A->sizeOfGood_ag_others == 1)
        && (strcmp(A->good_ag_others[0]->typeName, B) == 0)) {
        A->sizeOfGood_ag_others = 0;
    }
    else {
        for (int i = 0; i < A->sizeOfGood_ag_others; i++) {
            if (strcmp(A->good_ag_others[i]->typeName, B) == 0) {
                int j = i;
                for (; j < A->sizeOfGood_ag_others - 1; j++) {
                    A->good_ag_others[j] = A->good_ag_others[j + 1];
                }
                A->sizeOfGood_ag_others--;
                return success;
            }
        }
        return failure;
    }
    if (A->sizeOfGood_ag_others == 0) {
        A->good_ag_others[0] = NULL;
        return success;
    }
    return failure;
}

/*
 * Printing Functions:
 * each printing function recieve matching object, and print the object information
 * as requested according to inbal orders.
 */

void PrintPokemon(element elem) {
    if (elem == NULL)
        return;
    Pok* Pokemon = (Pok*)(elem);
    printf("%s :\n", Pokemon->name);
    printf("%s, %s Type. \n", Pokemon->species, Pokemon->Type->typeName);
    printf("Height: %.2f m    Weight: %.2f kg    Attack: %d \n \n",
           Pokemon->Det->height, Pokemon->Det->weight, Pokemon->Det->attack);
    return;
}

status PrintType(Type* pok_type) {
    if (pok_type == NULL)
        return failure;

    printf("Type %s -- %d pokemons \n", pok_type->typeName, pok_type->size);

    if (pok_type->sizeOfGood_ag_me != 0) {
        printTypeAgMe(pok_type);
    }
    if (pok_type->sizeOfGood_ag_others != 0) {
        printTypeAgOthers(pok_type);
    }
        printf("\n");
    return success;
}


void printTypeAgMe(Type* type_to) {

    printf("	These types are super-effective against %s:", type_to->typeName);
    for (int k = 0; k < type_to->sizeOfGood_ag_me; k++) {
        if (k == type_to->sizeOfGood_ag_me - 1) { //if we reach the last typeName to print, no need ","
            printf("%s\n", type_to->good_ag_me[k]->typeName);
            if (type_to->sizeOfGood_ag_others == 0)
                printf("\n");
            break;
        }
        printf("%s ,", type_to->good_ag_me[k]->typeName);
    }
}

void printTypeAgOthers(Type* type_to) {
    printf("	%s moves are super-effective against:", type_to->typeName);
    for (int k = 0; k < type_to->sizeOfGood_ag_others; k++) {
        if (k == type_to->sizeOfGood_ag_others - 1) { //if we reach the last typeName to print, no need ","
            printf("%s\n", type_to->good_ag_others[k]->typeName);
            break;
        }
        printf("%s ,", type_to->good_ag_others[k]->typeName);
    }
}

bool in_my_good_ag_me_list(Pok* A, Type* B)
{
    for (int i = 0; i < A->Type->sizeOfGood_ag_me; i++)
    {
        if (strcmp(A->Type->good_ag_me[i]->typeName,B->typeName)==0)
            return true;
    }
    return false;
}
bool in_my_good_ag_others_list(Pok* A, Type* B)
{
    for (int i = 0; i < A->Type->sizeOfGood_ag_others; i++)
    {
        if (strcmp(A->Type->good_ag_others[i]->typeName,B->typeName)==0)
            return true;
    }
    return false;
}


int compareAttack(element one, element two)
{
    if (one == NULL || two == NULL)
        return -2;

    Pok* A = (Pok*)(one);
    Pok* B = (Pok*)(two);

    int attack_A = A->Det->attack;
    int attack_B = B->Det->attack;

    if (attack_A >= attack_B)
        return 1;
    else
        return -1;
}

int compareAttackandType(element one, element two, int* attack1, int* attack2)
{
    if (one == NULL || two == NULL)
        return -9999;

    Pok* A = (Pok*)(one);
    Pok* B = (Pok*)(two);

    int attack_A = A->Det->attack;
    int attack_B = B->Det->attack;

    // if B is in A good ag me list AND A is in B good ag others list decrease ONLY ONCE
    if (in_my_good_ag_me_list(A, B->Type) || in_my_good_ag_others_list(B, A->Type)) {
        attack_A -= 10;
    }
    //if A is in B good ag me list AND B is in A good ag others list decrease ONLY ONCE
    if (in_my_good_ag_me_list(B, A->Type) || in_my_good_ag_others_list(A, B->Type)) {
        attack_B -= 10;
    }
    *attack1 = attack_A;
    *attack2 = attack_B;
    return attack_A-attack_B;

}

int compareEverything(element one, element two)
{
    if (one == NULL || two == NULL)
        return -2;

    Pok* A = (Pok*)(one);
    Pok* B = (Pok*)(two);

    if (strcmp(A->name, B->name) != 0)
        return -1;
    if (strcmp(A->Type->typeName, B->Type->typeName) != 0)
        return -1;
    if (strcmp(A->species, B->species) != 0)
        return -1;
    if(A->Det->attack != B->Det->attack)
        return -1;
    if (A->Det->weight != B->Det->weight)
        return -1;
    if (A->Det->height != B->Det->height)
        return -1;

    return 1;
}

element deepCopyPokemon(element elem)
{
    if (NULL==elem )
        return NULL;

    Pok* pok1 = (Pok*)(elem);

    char* pok2_name;
    char* pok2_species;

    pok2_species = (char*)malloc(strlen(pok1->species) * sizeof(char)+1);
    if(pok2_species == NULL)
    {
        return NULL;
    }

    pok2_name = (char*)malloc(strlen(pok1->name) * sizeof(char)+1);
    if(pok2_name == NULL)
    {
        free(pok2_species);
        return NULL;
    }

    strcpy(pok2_name, pok1->name);
    strcpy(pok2_species, pok1->species);

    Det* det2;

    det2 = createPokemonData(pok1->Det->height, pok1->Det->weight, pok1->Det->attack);

    Pok* pok2 = createPokemon(pok1->Type, det2, pok2_name, pok2_species);

    free(pok2_species);
    free(pok2_name);

    return pok2;
}

int CompareTypes(element one, element two)
{
    if ((one == NULL) || (two == NULL))
        return 0;

    char* A = (char*)(one);
    char* B = (char*)(two);
    return (strcmp(A,B)==0) ? 1 : 0;

}


char* getType(element elem)
{
    Pok* res = (Pok*)elem;
    return res->Type->typeName;
}

int getAttack(element elem)
{
    Pok* res = (Pok*)elem;
    return res->Det->attack;
}


