#include "pokemon_game_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define enemy_max_HP 5
#define Pokemon_count 5
#define Pokemon_Max_Level 6
#define Win_HP 10
#define Max_Name_Len 50
#define Num_Pokemon 6
#define Max_Party_Size 6

#define Max_Line_Len 1000
#define Max_Sqr_Len 100

//pika's level up count
int pika_L_up = 0;


int enemy_attack(int j, int fight_pokemon, char message_enemy_attack[][200])
{
    srand(time(NULL));
    int r_num = rand() % 2+1;
    printf("r_num:%d\n", r_num);

    int probability_hit = rand() % 100+1;
    printf("probability_hit:%d\n", probability_hit);

    if(r_num == 1)
    {
        if(enemy_party[j].attack1_accuracy >= probability_hit)
        {
            sprintf(message_enemy_attack[0], "%s\n", enemy_party[j].attack1);
            printf("%s\n", enemy_party[j].attack1);
            sprintf(message_enemy_attack[1], "%s got %d damage\n", pika_party[fight_pokemon].name, enemy_party[j].attack1_power);
            printf("%s got %d damage\n", pika_party[fight_pokemon].name, enemy_party[j].attack1_power);
            pika_party[fight_pokemon].hp -= enemy_party[j].attack1_power;
            if(pika_party[fight_pokemon].hp <= 0)
            {
                pika_party[fight_pokemon].hp = 0;
            }
            printf("pika_hp:%d\n", pika_party[fight_pokemon].hp);
            return 3;     
        }

        else
        {
            sprintf(message_enemy_attack[2], "attack missed\n");
            printf("attack missed\n");
            return 4;
        }
    }
    else if(r_num == 2)
    {
        if(enemy_party[j].attack2_accuracy >= probability_hit)
        {
            sprintf(message_enemy_attack[0], "%s\n", enemy_party[j].attack2);
            printf("%s\n", enemy_party[j].attack2);
            sprintf(message_enemy_attack[1], "%s got %d damage\n", pika_party[fight_pokemon].name, enemy_party[j].attack2_power);
            printf("%s got %d damage\n", pika_party[fight_pokemon].name, enemy_party[j].attack2_power);
            pika_party[fight_pokemon].hp -= enemy_party[j].attack2_power; 
            if(pika_party[fight_pokemon].hp <= 0)
            {
                pika_party[fight_pokemon].hp = 0;
            }
            printf("pika_hp:%d\n", pika_party[fight_pokemon].hp);
            return 3;   
        }

        else
        {
            sprintf(message_enemy_attack[2], "attack missed\n");
            printf("attack missed\n");
            return 4;
        }
    }
}

//pika_party_attack
int pika_attack(int fight_pokemon,int j, int attack_choice_pika, char message_pika_attack[][300])
{

    srand(time(NULL));
    int probability_hit = rand() % 100+1;
    printf("%d\n", probability_hit);
    

    
    if(attack_choice_pika == 1)
    {
        if(pika_party[fight_pokemon].attack1_accuracy >= probability_hit)
        {
            sprintf(message_pika_attack[2], "%s\n", pika_party[fight_pokemon].attack1);
            sprintf(message_pika_attack[3], "%s got %d damage\n", enemy_party[j].name, pika_party[fight_pokemon].attack1_power);
            printf("%s\n", pika_party[fight_pokemon].attack1);
            printf("%s got %d damage\n", enemy_party[j].name, pika_party[fight_pokemon].attack1_power);
            enemy_party[j].hp -= pika_party[fight_pokemon].attack1_power;
            if(enemy_party[j].hp <= 0)
            {
                enemy_party[j].hp = 0;
            }
            printf("enemy_hp:%d\n", enemy_party[j].hp);
            return 3;
            
        }
        else
        {
            sprintf(message_pika_attack[4], "attack missed\n");
            printf("attack missed\n");
            return 4;
        }

    }
    else if(attack_choice_pika == 2)
    {
        if(pika_party[fight_pokemon].attack1_accuracy >= probability_hit)
        {
            sprintf(message_pika_attack[2], "%s\n", pika_party[fight_pokemon].attack2);
            sprintf(message_pika_attack[3], "%s got %d damage\n", enemy_party[j].name, pika_party[fight_pokemon].attack2_power);
            printf("%s\n", pika_party[fight_pokemon].attack2);
            printf("%s got %d damage\n", enemy_party[j].name, pika_party[fight_pokemon].attack2_power);
            enemy_party[j].hp -= pika_party[fight_pokemon].attack2_power;
            if(enemy_party[j].hp <= 0)
            {
                enemy_party[j].hp = 0;
            }
            printf("enemy_hp:%d\n", enemy_party[j].hp);
            return 3;
            
        }
        else
        {
            sprintf(message_pika_attack[4], "attack missed\n");
            printf("attack missed\n");
            return 4;
        }
    }
}

