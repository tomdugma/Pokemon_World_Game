#ifndef PokedexDefs2
#define PokedexDefs2

#include "Defs.h"

/*
 * Struct pokemon_type:
 * includes char* name, int size, and 2 counters to both arrays
 */
typedef struct pokemon_Type {
    char* typeName;
    int size;
    int sizeOfGood_ag_me;
    int sizeOfGood_ag_others;

    struct pokemon_Type** good_ag_me;
    struct pokemon_Type** good_ag_others;
}Type;

/*
 * Struct pokemon_data, holds information about the weight, height, and attack power of the pokemon
 */
typedef struct pokemon_Det {
    double height;
    double weight;
    int attack;
}Det;

/*
 * Struct pokemon, contain both type and data structs inside of him, also has char* name, and char* species.
 */
typedef struct Pokemon {
    char* name;
    char* species;
    Type* Type;
    Det* Det;
}Pok;


/*
 * ----- functions that will be implemented in the source file -----
 */
Pok* createPokemon(Type* type, Det* det, char* name, char* species);

void PokDestroy(element elem);

Type* createPokemonType(char* name);

status TypeDestroy(Type* type_to_des);

Det* createPokemonData(double hight, double weight, int attack);

status add_effective_ag_me(Type* A, Type* B);

status add_effective_ag_others(Type* A, Type* B);

status delete_from_effective_ag_me(Type* A, char* B);

status delete_from_effective_ag_others(Type* A, char* B);

//int countTypes(Type* Typeto, Pok* Pokemons_arr[], int numberOfPokemons);

void PrintPokemon(element elem);

status PrintType(Type* pok_type);

void printTypeAgMe(Type* type_to);

void printTypeAgOthers(Type* type_to);

// added in C3

int compareAttack(element one, element two);

int compareAttackandType(element one, element two, int* attack1, int* attack2);

int compareEverything(element one, element two);

element deepCopyPokemon(element elem);

void printOneType(Pok* pokemon);


int CompareTypes(element one, element two);

int getAttack(element elem);

char* getType(element elem);


#endif
