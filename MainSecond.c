#include "Pokemon.h"
#include "BattleByCategory.h"


int main(int argc, char *argv[]) {

    //init
    bool args = true;
    int numberOfTypes = atoi(argv[1]);
    if (numberOfTypes == 0) {
        puts("Error: number of Types given is 0");
        args = false;
    }
    int capacityInType = atoi(argv[2]);
    if (capacityInType == 0) {
        puts("Error: number of maximum Pokemons per battle given is 0");
        args = false;
    }
    char *configurationFile = argv[3];
    if (args == true) {
        Type** Types_arr = (Type**) malloc(sizeof(Type*) * numberOfTypes);
        if (Types_arr == NULL)
            puts("Error allocating memory");

        Battle Pokemons_Battles;

//Assist function:
        Type* SearchforType(char *name) {
            for (int i = 0; i < numberOfTypes; i++) {
                if (strcmp(Types_arr[i]->typeName, name) == 0) {
                    return Types_arr[i];
                }
            }
            return NULL;
        }
// File reading:
        FILE *fp;
        fp = fopen(configurationFile, "r");
        if (fp == NULL) {
            printf("Can't open file\n");
        }
        char readstring1[300];
        char readstring2[300];

        char *check;
        char *token1;
        char *token2;

        //scanning file
        fscanf(fp, "%s", readstring1);
        if (strcmp(readstring1, "Types") != 0) {
            printf("Types not found\n");
        } else {
            fscanf(fp, "%s", readstring1);
            char* token3 = (char*)malloc(sizeof(char)*strlen(readstring1)+1);
            strcpy(token3,readstring1);
            while (feof(fp) == 0) {
                if (strcmp(readstring1, "Pokemons") != 0) {
                    token1 = strtok(readstring1, ",");
                    for (int i = 0; i < numberOfTypes; i++) {
                        Type *new_type = createPokemonType(token1);
                        if (new_type == NULL) {
                            puts("No memory available.");
                            return -1;
                        }
                        Types_arr[i] = new_type;
                        token1 = strtok(NULL, ",");
                    }
                    fscanf(fp, "%s", readstring1);

                    Pokemons_Battles = createBattleByCategory(capacityInType,
                                                              numberOfTypes, token3, compareAttack,
                                                              deepCopyPokemon, PokDestroy, getType,
                                                              compareAttackandType, PrintPokemon);


                    while (strcmp(readstring1, "Pokemons") != 0) {
                        fscanf(fp, "%s", readstring2);
                        check = strstr(readstring2, "effective-against-me:");
                        if (check != NULL) {
                            token1 = strstr(check, ":");
                            token1 += 1;

                            token2 = strtok(token1, ",");

                            Type* add_to_type;
                            add_to_type = SearchforType(readstring1);
                            if (add_to_type == NULL)
                                printf(
                                        "Error: type (%s) not found in types list\n",
                                        readstring1);
                            do {

                                Type* type_to_add;
                                type_to_add = SearchforType(token2);
                                if (type_to_add == NULL)
                                    printf(
                                            "Error: type (%s) not found in types list\n",
                                            token2);
                                status curr;
                                curr = add_effective_ag_me(add_to_type,
                                                           type_to_add);
                                if (curr == failure) {
                                    puts("No memory available.");
                                    return -1;
                                }

                                token2 = strtok(NULL, ",");
                            } while (token2 != NULL);

                        } else {
                            check = strstr(readstring2,
                                           "effective-against-other:");
                            if (check != NULL) {
                                token1 = strstr(check, ":");
                                token1 += 1;

                                token2 = strtok(token1, ",");

                                Type* add_to_type;
                                add_to_type = SearchforType(readstring1);
                                if (add_to_type == NULL)
                                    printf(
                                            "Error: type (%s) not found in types list\n",
                                            readstring1);
                                do {

                                    Type* type_to_add;
                                    type_to_add = SearchforType(token2);
                                    if (type_to_add == NULL)
                                        printf(
                                                "Error: type (%s) not found in types list\n",
                                                token2);
                                    status curr2;
                                    curr2 = add_effective_ag_others(add_to_type,
                                                                    type_to_add);
                                    if (curr2 == failure) {
                                        puts("No memory available.");
                                        return -1;
                                    }

                                    token2 = strtok(NULL, ",");
                                } while (token2 != NULL);

                            }
                        }
                        fscanf(fp, "%s", readstring1);
                    } // end of scanning types
                } // end of scanning types
                else {
                    while (fscanf(fp, "%s", readstring1) == 1) {

                        char pokemons[6][20];
                        if (readstring1 == NULL)
                            break;

                        int j = 0;
                        for (token1 = strtok(readstring1, ","); token1 && j < 6;
                             token1 = strtok(NULL, ",")) {
                            strcpy(pokemons[j], token1);

                            j++;
                        }

                        Det *pokemon_details = createPokemonData(
                                atof(pokemons[2]), atof(pokemons[3]),
                                atoi(pokemons[4]));
                        if (pokemon_details == NULL)
                            printf("No memory available.\n");
                        Type* type_to_add;
                        type_to_add = SearchforType(pokemons[5]);
                        if (type_to_add == NULL)
                            printf("Error: type (%s) not found in types list\n",
                                   pokemons[5]);
                        Pok *pokemon = createPokemon(type_to_add,
                                                     pokemon_details, pokemons[0], pokemons[1]);

                        if (pokemon == NULL)
                            printf("No memory available.\n");


                        status check = insertObject(Pokemons_Battles, pokemon);
                        PokDestroy(pokemon);
                        if (check == failure)
                            printf("Error\n");

                    }
                    break;

                }
                free(token3);
            }
        }


        fclose(fp);

         void printAllTypes(Type *Types_arr[],
                             int numberOfTypes) {
            //int curr;
            for (int i = 0; i < numberOfTypes; i++) {
            	PrintType(Types_arr[i]);
            }
        }

        bool CheckIfTypeExistInList(Type* Main_Type, Type* Check_Type,
                                    type_check which_list) {
            // checking if Check_Type exists in Main_Type effective against me/other list (which_list)
            if (Main_Type == NULL || Check_Type == NULL)
                return false;
            if (which_list == me) {
                for (int i = 0; i < Main_Type->sizeOfGood_ag_me; i++) {
                    if (strcmp(Main_Type->good_ag_me[i]->typeName,
                               Check_Type->typeName) == 0) {
                        return true;
                    }
                }
                return false;
            }
            if (which_list == others) {
                for (int i = 0; i < Main_Type->sizeOfGood_ag_others; i++) {
                    if (strcmp(Main_Type->good_ag_others[i]->typeName,
                               Check_Type->typeName) == 0) {
                        return true;
                    }
                }
                return false;
            }
            return false;
        }

        //status funcs;
        bool switch_c = true;
        int ch;

        while (switch_c) {
            printf("Please choose one of the following numbers:\n");
            printf("1: Print all Pokemons by types\n");
            printf("2: Print all Pokemons types\n");
            printf("3: Insert Pokemon to battles training camp\n");
            printf("4: Remove stronger Pokemon by type\n");
            printf("5: Fight\n");
            printf("6: Exit\n");
            int choice = scanf("%d", &ch); // must have space when recieving char, otherwise everything messed up
            if (choice < 1) {
                char letter;
                puts("Please choose a valid number.");
                scanf("%c", &letter);
            } else {
                switch (ch) {

                    case 1: /*  Print all Pokemons by types */
                        displayObjectsByCategories(Pokemons_Battles);
                        break;

                    case 2: /* Print all pokemon types */
                        printAllTypes(Types_arr, numberOfTypes);

                        break;

                    case 3: /* Insert Pokemon to battles training camp */
                        printf("Please enter Pokemnon type name:\n");
                        scanf("%s", readstring1);
                        Type* add_to_type;
                        add_to_type = SearchforType(readstring1);
                        if (add_to_type == NULL) {
                            printf("Type name doesn`t exist.\n");
                            break;
                        }
                        if (add_to_type->size == capacityInType) {
                            printf("Type at full capacity.\n");
                            break;
                        }
                        printf("Please enter Pokemon name:\n");
                        scanf("%s", readstring2);
                        char pok_name[Buffersize];
                        strcpy(pok_name, readstring2);
                        printf("Please enter Pokemon species:\n");
                        scanf("%s", readstring2);
                        char pok_species[Buffersize];
                        strcpy(pok_species, readstring2);
                        printf("Please enter Pokemon height:\n");
                        scanf("%s", readstring2);
                        double pok_h = atof(readstring2);
                        printf("Please enter Pokemon weight:\n");
                        scanf("%s", readstring2);
                        double pok_w = atof(readstring2);
                        printf("Please enter Pokemon attack:\n");
                        scanf("%s", readstring2);
                        int pok_a = atoi(readstring2);
                        Det *new_pok_det = createPokemonData(pok_h, pok_w, pok_a);
                        Pok* new_pok = createPokemon(add_to_type, new_pok_det,
                                                     pok_name, pok_species);
                        status check = insertObject(Pokemons_Battles, new_pok);
                        if (check == failure)
                            printf("Error\n");
                        printf("The Pokemon was successfully added.\n");
                        PrintPokemon(new_pok);
                        PokDestroy(new_pok);
                        break;
//
                    case 4: /* Remove strongest Pokemon by type */
                        printf("Please enter type name:\n");
                        scanf("%s", readstring1);

                        add_to_type = SearchforType(readstring1);
                        if (add_to_type == NULL) {
                            printf("Type name doesn`t exist.\n");
                            break;
                        }
                        Pok* max_pok = removeMaxByCategory(Pokemons_Battles,
                                                           readstring1);
                        if (max_pok == NULL) {
                            printf("There is no Pokemon to remove.\n");
                            break;
                        }
                        printf("the strongest Pokemon was removed:\n");
                        PrintPokemon(max_pok);
                        PokDestroy(max_pok);
                        //max_pok->Type->size--;
                        break;

                    case 5: /* Fight */
                        printf("Please enter Pokemnon type name:\n");
                        scanf("%s", readstring1);
                        Type* pok_fight_type;
                        pok_fight_type = SearchforType(readstring1);
                        if (pok_fight_type == NULL) {
                            printf("Type name doesn`t exist.\n");
                            break;
                        }
                        printf("Please enter Pokemon name:\n");
                        scanf("%s", readstring2);
                        char pok_fight_name[Buffersize];
                        strcpy(pok_fight_name, readstring2);
                        printf("Please enter Pokemon species:\n");
                        scanf("%s", readstring2);
                        char pok_fight_species[Buffersize];
                        strcpy(pok_fight_species, readstring2);
                        printf("Please enter Pokemon height:\n");
                        scanf("%s", readstring2);
                        double pok_f_h = atof(readstring2);
                        printf("Please enter Pokemon weight:\n");
                        scanf("%s", readstring2);
                        double pok_f_w = atof(readstring2);
                        printf("Please enter Pokemon attack:\n");
                        scanf("%s", readstring2);

                        int pok_f_a = atoi(readstring2);

                        Det *new_pok_f_det = createPokemonData(pok_f_h, pok_f_w,
                                                               pok_f_a);

                        Pok* new_f_pok = createPokemon(pok_fight_type,
                                                       new_pok_f_det, pok_fight_name, pok_fight_species);

                        printf("you choose to fight with:\n");
                        PrintPokemon(new_f_pok);
                        element winner = fight(Pokemons_Battles, new_f_pok);
                        PokDestroy(new_f_pok);
                        if (winner == NULL)
                            break;

                        break;

                    case 6: /* Exit program and cleaning all data. */
                        destroyBattleByCategory(Pokemons_Battles);

                        for (int m = numberOfTypes - 1; m >= 0; m--) {
                            TypeDestroy(Types_arr[m]);
                        }
                        free(Types_arr); // maybe need to free each cell

                        printf(
                                "All the memory cleaned and the program is safely closed.\n");
                        switch_c = false;


                        break;

                    default:
                        puts("Please choose a valid number.");
                }
            }
        }
    }
}
