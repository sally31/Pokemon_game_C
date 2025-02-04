#include "pokemon_game_func.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int second2 = 2;
int Double = 2;
float Half = 0.5;
char buffer[200];

void type_pokemon_enemy_attack(Pokemon enemy_party[], Pokemon pika_party[], int j, int fight_pokemon, char messages[][256])
{
    //fire
    //ghost->０, normal->２
    //if enemy is fire(attack)
    printf("1\n");
    if(strcmp(enemy_party[j].type, "fire")==0 && strcmp(pika_party[fight_pokemon].type, "ghost")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power = 0;
        enemy_party[j].attack2_power = 0;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became 0\n", enemy_party[j].name);
        printf("%s's attack power became 0\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
        
    }
    else if(strcmp(enemy_party[j].type, "fire")==0 && strcmp(pika_party[fight_pokemon].type, "normal")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Double;
        enemy_party[j].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", enemy_party[j].name);
        printf("%s's attack power became Double\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }

    //electric
    //electric->0.5, fireに->0.5, fairy->２
    //enemy is electric(attack)
    else if(strcmp(enemy_party[j].type, "electric")==0 && strcmp(pika_party[fight_pokemon].type, "electric")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Half;
        enemy_party[j].attack2_power *= Half;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Half\n", enemy_party[j].name);
        printf("%s's attack power became Half\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }
    else if(strcmp(enemy_party[j].type, "electric")==0 && strcmp(pika_party[fight_pokemon].type, "fire")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Half;
        enemy_party[j].attack2_power *= Half;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Half\n", enemy_party[j].name);
        printf("%s's attack power became Half\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }
    else if(strcmp(enemy_party[j].type, "electric")==0 && strcmp(pika_party[fight_pokemon].type, "fairy")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Double;
        enemy_party[j].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", enemy_party[j].name);
        printf("%s's attack power became Double\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }

    //ghost
    //ghost->２, electric->２
    //enemy is ghost(attack)
    else if(strcmp(enemy_party[j].type, "ghost")==0 && strcmp(pika_party[fight_pokemon].type, "ghost")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Double;
        enemy_party[j].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became double\n", enemy_party[j].name);
        printf("%s's attack power became double\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }
    else if(strcmp(enemy_party[j].type, "ghost")==0 && strcmp(pika_party[fight_pokemon].type, "electric")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Double;
        enemy_party[j].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", enemy_party[j].name);
        printf("%s's attack power became Double\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }

    //normal
    //ghost->0.5, fairy->２
    else if(strcmp(enemy_party[j].type, "normal")==0 && strcmp(pika_party[fight_pokemon].type, "ghost")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Half;
        enemy_party[j].attack2_power *= Half;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Half\n", enemy_party[j].name);
        printf("%s's attack power became Half\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }
    else if(strcmp(enemy_party[j].type, "normal")==0 && strcmp(pika_party[fight_pokemon].type, "fairy")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Double;
        enemy_party[j].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", enemy_party[j].name);
        printf("%s's attack power became Double\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }

    //fairy
    //ghost->２, fire->２, electric->0.5
    else if(strcmp(enemy_party[j].type, "fairy")==0 && strcmp(pika_party[fight_pokemon].type, "ghost")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Double;
        enemy_party[j].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", enemy_party[j].name);
        printf("%s's attack power became Double\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }
    else if(strcmp(enemy_party[j].type, "fairy")==0 && strcmp(pika_party[fight_pokemon].type, "fire")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Double;
        enemy_party[j].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", enemy_party[j].name);
        printf("%s's attack power became Double\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }
    else if(strcmp(enemy_party[j].type, "fairy")==0 && strcmp(pika_party[fight_pokemon].type, "electric")==0)
    {
        sprintf(messages[0], "pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        printf("pika party's pikemon %s's type is %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].type);
        enemy_party[j].attack1_power *= Half;
        enemy_party[j].attack2_power *= Half;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Half\n", enemy_party[j].name);
        printf("%s's attack power became Half\n", enemy_party[j].name);
        printf("a1_p:%d a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);
    }
    else
    {
        sprintf(messages[0], "%s's type didn't efect to %s", pika_party[fight_pokemon].name, enemy_party[j].name);
        sprintf(messages[1], "%s's power didn't change", enemy_party[j].name);
        printf("%s's type didn't efect to %s\n", pika_party[fight_pokemon].name, enemy_party[j].name);
        printf("%s's power didn't change\n", enemy_party[j].name);
    }

}

//, char messages[][256]

void type_pokemon_pika_attack(Pokemon enemy_party[], Pokemon pika_party[], int j, int fight_pokemon, char messages[][256])
{
    //fire
    //ghost->０, normal->２
    //if pika is fire(attack)
    printf("2\n");
    if(strcmp(pika_party[fight_pokemon].type, "fire")==0 && strcmp(enemy_party[j].type, "ghost")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power = 0;
        pika_party[fight_pokemon].attack2_power = 0;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became 0\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became 0\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }
    else if(strcmp(pika_party[fight_pokemon].type, "fire")==0 && strcmp(enemy_party[j].type, "normal")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Double;
        pika_party[fight_pokemon].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }

    //electric
    //electric->0.5, fireに->0.5, fairy->２
    //pika is electric(attack)
    else if(strcmp(pika_party[fight_pokemon].type, "electric")==0 && strcmp(enemy_party[j].type, "electric")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Half;
        pika_party[fight_pokemon].attack2_power *= Half;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Half\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Half\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }
    else if(strcmp(pika_party[fight_pokemon].type, "electric")==0 && strcmp(enemy_party[j].type, "fire")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Half;
        pika_party[fight_pokemon].attack2_power *= Half;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Half\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Half\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }
    else if(strcmp(pika_party[fight_pokemon].type, "electric")==0 && strcmp(enemy_party[j].type, "fairy")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Double;
        pika_party[fight_pokemon].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }

    //ghost
    //ghost->２, electric->２
     //pika is ghost(attack)
    else if(strcmp(pika_party[fight_pokemon].type, "ghost")==0 && strcmp(enemy_party[j].type, "ghost")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Double;
        pika_party[fight_pokemon].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }
    else if(strcmp(pika_party[fight_pokemon].type, "ghost")==0 && strcmp(enemy_party[j].type, "electric")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Double;
        pika_party[fight_pokemon].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }

    //normal
    //ghost->0.5, fairy->２
    else if(strcmp(pika_party[fight_pokemon].type, "normal")==0 && strcmp(enemy_party[j].type, "ghost")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Half;
        pika_party[fight_pokemon].attack2_power *= Half;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Half\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Half\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }
    else if(strcmp(pika_party[fight_pokemon].type, "normal")==0 && strcmp(enemy_party[j].type, "fairy")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Double;
        pika_party[fight_pokemon].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }

    //fairy
    //ghost->２, fire->２, electric->0.5
    else if(strcmp(pika_party[fight_pokemon].type, "fairy")==0 && strcmp(enemy_party[j].type, "ghost")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Double;
        pika_party[fight_pokemon].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }
    else if(strcmp(pika_party[fight_pokemon].type, "fairy")==0 && strcmp(enemy_party[j].type, "fire")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Double;
        pika_party[fight_pokemon].attack2_power *= Double;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Double\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }
    else if(strcmp(pika_party[fight_pokemon].type, "fairy")==0 && strcmp(enemy_party[j].type, "electric")==0)
    {
        sprintf(messages[0], "enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        printf("enemy party's pikemon %s's type is %s\n", enemy_party[j].name, enemy_party[j].type);
        pika_party[fight_pokemon].attack1_power *= Half;
        pika_party[fight_pokemon].attack2_power *= Half;
        sleep(second2);
        sprintf(messages[1], "%s's attack power became Half\n", pika_party[fight_pokemon].name);
        printf("%s's attack power became Half\n", pika_party[fight_pokemon].name);
        printf("a1_p:%d a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);
    }
    else
    {
        sprintf(messages[0], "%s's type didn't efect to %s", enemy_party[j].name, pika_party[fight_pokemon].name);
        sprintf(messages[1], "%s's power didn't change", pika_party[fight_pokemon].name);
        printf("%s's type didn't efect to %s\n", enemy_party[j].name, pika_party[fight_pokemon].name);
        printf("%s's power didn't change\n", pika_party[fight_pokemon].name);
    }
}