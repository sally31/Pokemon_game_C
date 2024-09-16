#ifndef POKEMON_GAME_FUNC_H
#define POKEMON_GAME_FUNC_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define Max_Name_Len 50
#define Num_Pokemon 5
#define Max_Party_Size 6

typedef struct
{
    char name[Max_Name_Len];
    int level;
    int hp;
    int active;
}Pokemon;

Pokemon createPokemon(const char *name, int level, int hp, int active);

Pokemon enemy_party[Num_Pokemon];

Pokemon pika_party[Max_Party_Size];

void processCSV_enemy(const char *file_enemy_party, Pokemon enemy_party[], int *party_size, int active);
void export_enemy_CSV(const char *file_save_enemy, Pokemon enemy_party[]);
void inport_from_export_enemy_CSV(const char *file_save_enemy, Pokemon enemy_party[], int *party_size, int active);

void processCSV_pika(const char *file_pika_party, Pokemon pika_party[], int *party_size, int active);
void export_pika_CSV(const char *file_save_pika, Pokemon pika_party[], int pika_party_size);
void inport_from_export_pika_CSV(const char *file_save_pika, Pokemon pika_party[], int *party_size, int active);


#endif