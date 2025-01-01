#ifndef POKEMON_GAME_FUNC_H
#define POKEMON_GAME_FUNC_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define Max_Name_Len 50
#define Num_Pokemon 6
#define Max_Party_Size 6

typedef struct
{
    char name[Max_Name_Len];
    int level;
    int hp;
    /*new26/6/2024*/char type[Max_Name_Len];
    /*new26/6/2024*/char attack1[Max_Name_Len];
    /*new26/6/2024*/int attack1_power;
    /*new26/6/2024*/int attack1_accuracy;
    /*new26/6/2024*/char attack2[Max_Name_Len];
    /*new26/6/2024*/int attack2_power;
    /*new26/6/2024*/int attack2_accuracy;
    /*new26/6/2024*/int  speed;
    int active;
}Pokemon;


Pokemon createPokemon(const char *name, int level, int hp,
 const char *type, const char *attack1,int attack1_power,
 int attack1_accuracy, const char *attack2,int attack2_power,
 int attack2_accuracy, int speed, int active);


// Pokemon createPokemon(const char *name, int level, int hp, 
//  const char *type, const char *attack1, int attack1_power,
//  int attack1_accuracy, const char *attack2, int attack2_power,
//  int attack2_accuracy, int speed, int active);


Pokemon enemy_party[Num_Pokemon];

Pokemon pika_party[Max_Party_Size];

void processCSV_enemy(const char *file_enemy_party, Pokemon enemy_party[], int *party_size, int active);
void export_enemy_CSV(const char *file_save_enemy, Pokemon enemy_party[]);
void inport_from_export_enemy_CSV(const char *file_save_enemy, Pokemon enemy_party[], int *party_size, int active);

void processCSV_pika(const char *file_pika_party, Pokemon pika_party[], int *party_size, int active);
void export_pika_CSV(const char *file_save_pika, Pokemon pika_party[], int pika_party_size);
void inport_from_export_pika_CSV(const char *file_save_pika, Pokemon pika_party[], int *party_size, int active);

void type_pokemon_enemy_attack(Pokemon enemy_party[], Pokemon pika_party[], int j, int fight_pokemon);
void type_pokemon_pika_attack(Pokemon enemy_party[], Pokemon pika_party[], int j, int fight_pokemon);


#endif