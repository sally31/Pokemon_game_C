#include "pokemon_game_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define Max_Name_Len 50
#define Max_Party_Size 6

#define Max_Line_Len 1000
#define Max_Sqr_Len 100

Pokemon createPokemon(const char *name, int level, int hp,
 const char *type, const char *attack1,int attack1_power,
 int attack1_accuracy, const char *attack2,int attack2_power,
 int attack2_accuracy, int speed, int active)
{
    Pokemon newPokemon;
    strcpy(newPokemon.name, name);
    newPokemon.name[Max_Name_Len - 1] = '\0'; 
    newPokemon.level = level;
    newPokemon.hp = hp;
    strncpy(newPokemon.type, type, Max_Name_Len - 1);
    newPokemon.type[Max_Name_Len - 1] = '\0'; 
    strncpy(newPokemon.attack1, attack1, Max_Name_Len - 1);
    newPokemon.attack1[Max_Name_Len - 1] = '\0'; 
    newPokemon.attack1_power = attack1_power;
    newPokemon.attack1_accuracy = attack1_accuracy;
    strncpy(newPokemon.attack2, attack2, Max_Name_Len - 1);
    newPokemon.attack2[Max_Name_Len - 1] = '\0'; 
    newPokemon.attack2_power = attack2_power;
    newPokemon.attack2_accuracy = attack2_accuracy;
    newPokemon.speed = speed;
    newPokemon.active = active; 
    return newPokemon;
}



void processCSV_pika(const char *file_pika_party, Pokemon pika_party[], int *party_size, int active)
{
     FILE *file = fopen(file_pika_party, "r");
    if(!file)
    {
        perror("error - pika file not found");
        return;
    }

    char line[Max_Line_Len];
    int index = 0;
 
    //delete the title on the first line
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return;
    }
    
    //get the info from the second line and put it in the list(pika_party)
    while (fgets(line, sizeof(line), file))
    {
        char *token;
        char *rest = line;

        char name[Max_Name_Len];
        int level = 0;
        int hp = 0;
        /*new26/6/2024*/char type[Max_Name_Len];
        /*new26/6/2024*/char attack1[Max_Name_Len];
        /*new26/6/2024*/int attack1_power = 0;
        /*new26/6/2024*/int attack1_accuracy = 0;
        /*new26/6/2024*/char attack2[Max_Name_Len];
        /*new26/6/2024*/int attack2_power = 0;
        /*new26/6/2024*/int attack2_accuracy = 0;
        /*new26/6/2024*/int  speed = 0;

        //while((token = strtok_r(rest, ",", &rest)))
        token = strtok_r(rest, ",", &rest);
        if(token) strncpy(name, token, Max_Name_Len-1);
        name[Max_Name_Len - 1] = '\0';

        token = strtok_r(rest, ",", &rest);
        if(token) level = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) hp = atoi(token);


        /*ここから追加した情報26/6/2024*/

        token = strtok_r(rest, ",", &rest);
        if(token) strncpy(type, token, Max_Name_Len-1);
        type[Max_Name_Len - 1] = '\0';

        token = strtok_r(rest, ",", &rest);
        if(token) strncpy(attack1, token, Max_Name_Len-1);
        attack1[Max_Name_Len - 1] = '\0';

        token = strtok_r(rest, ",", &rest);
        if(token) attack1_power = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) attack1_accuracy = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) strncpy(attack2, token, Max_Name_Len-1);
        attack2[Max_Name_Len - 1] = '\0';

        token = strtok_r(rest, ",", &rest);
        if(token) attack2_power = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) attack2_accuracy = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) speed = atoi(token);

        /*ここまで*/

        token = strtok_r(rest, ",", &rest);
        if(token) active = atoi(token);
        
        pika_party[index] = createPokemon(name, level, hp, type, 
        attack1, attack1_power, attack1_accuracy, attack2,
        attack2_power, attack2_accuracy, speed, active);
        printf("name:%s\n", pika_party[index].name);
        printf("level:%d\n", pika_party[index].level);
        printf("hp:%d\n", pika_party[index].hp);
        printf("type:%s\n", pika_party[index].type);
        printf("attack:%s\n", pika_party[index].attack1);
        printf("a1_power:%d\n", pika_party[index].attack1_power);
        printf("a1_accuracy:%d\n", pika_party[index].attack1_accuracy);
        printf("attack2:%s\n", pika_party[index].attack2);
        printf("a2_power:%d\n", pika_party[index].attack2_power);
        printf("a2_accuracy:%d\n", pika_party[index].attack2_accuracy);
        printf("speed:%d\n", pika_party[index].speed);
        printf("active:%d\n", pika_party[index].active);
        index++;
        printf("\n");
    }
    *party_size = index;
    fclose(file);
}

void export_pika_CSV(const char *file_save_pika, Pokemon pika_party[], int pika_party_size)
{
    FILE *file = fopen(file_save_pika, "w");
    if(file == NULL)
    {
        perror("can't open file");
        return;
    }

    fprintf(file, "name, level, hp, type, attack1, attack1_power, attack1_accuracy, attack2, attack2_power, attack2_accuracy, speed, active\n");

    for(int y = 0; y < pika_party_size; y++)
    {
        printf("name: %s\n", pika_party[y].name);
        printf("level: %d\n", pika_party[y].level);
        printf("hp: %d\n", pika_party[y].hp);
        printf("type: %s\n", pika_party[y].type);
        printf("attack1: %s\n", pika_party[y].attack1);
        printf("attack1_power: %d\n", pika_party[y].attack1_power);
        printf("attack1_accuracy: %d\n", pika_party[y].attack1_accuracy);
        printf("attack2: %s\n", pika_party[y].attack2);
        printf("attack2_power: %d\n", pika_party[y].attack2_power);
        printf("attack2_accuracy: %d\n", pika_party[y].attack2_accuracy);
        printf("speed: %d\n", pika_party[y].speed);
        printf("active: %d\n", pika_party[y].active);
        printf("\n");

        fprintf(file, "%s, %d, %d, %s, %s, %d, %d, %s, %d, %d, %d, %d\n", pika_party[y].name, pika_party[y].level,
        pika_party[y].hp, pika_party[y].type, pika_party[y].attack1, pika_party[y].attack1_power, pika_party[y].attack1_accuracy,
        pika_party[y].attack2, pika_party[y].attack2_power, pika_party[y].attack2_accuracy, pika_party[y].speed, 
        pika_party[y].active);
    }
    fclose(file);
}

/*____________________________________________________________________________*/
/*セーブしたデータをインポートする*/

void inport_from_export_pika_CSV(const char *file_save_pika, Pokemon pika_party[], int *party_size, int active)
{
    //ファイルの読み込み
    FILE *file = fopen(file_save_pika, "r");
    if(!file)
    {
        perror("error - enemy file not found");
        return;
    }

    char line[Max_Line_Len];
    int index = 0;
 
    //delete the title on the first line
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return;
    }
    
    //get the info from the second line and put it in the list(enemy_party)
    while (fgets(line, sizeof(line), file))
    {
        char *token;
        char *rest = line;

        char name[Max_Name_Len];
        int level = 0;
        int hp = 0;
        /*new26/6/2024*/char type[Max_Name_Len];
        /*new26/6/2024*/char attack1[Max_Name_Len];
        /*new26/6/2024*/int attack1_power = 0;
        /*new26/6/2024*/int attack1_accuracy = 0;
        /*new26/6/2024*/char attack2[Max_Name_Len];
        /*new26/6/2024*/int attack2_power = 0;
        /*new26/6/2024*/int attack2_accuracy = 0;
        /*new26/6/2024*/int  speed = 0;

        //while((token = strtok_r(rest, ",", &rest)))
        token = strtok_r(rest, ",", &rest);
        if(token) strncpy(name, token, Max_Name_Len-1);
        name[Max_Name_Len - 1] = '\0'; 

        token = strtok_r(rest, ",", &rest);
        if(token) level = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) hp = atoi(token);

        /*ここから追加した情報26/6/2024*/

        token = strtok_r(rest, ",", &rest);
        if(token) strncpy(type, token, Max_Name_Len-1);
        type[Max_Name_Len - 1] = '\0'; 

        token = strtok_r(rest, ",", &rest);
        if(token) strncpy(attack1, token, Max_Name_Len-1);
        attack1[Max_Name_Len - 1] = '\0'; 

        token = strtok_r(rest, ",", &rest);
        if(token) attack1_power = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) attack1_accuracy = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) strncpy(attack2, token, Max_Name_Len-1);
        attack2[Max_Name_Len - 1] = '\0'; 

        token = strtok_r(rest, ",", &rest);
        if(token) attack2_power = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) attack2_accuracy = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) speed = atoi(token);

        /*ここまで*/

        token = strtok_r(rest, ",", &rest);
        if(token) active = atoi(token);
        
        pika_party[index] = createPokemon(name, level, hp, type, 
        attack1, attack1_power, attack1_accuracy, attack2,
        attack2_power, attack2_accuracy, speed, active);
        printf("name:%s\n", pika_party[index].name);
        printf("level:%d\n", pika_party[index].level);
        printf("hp:%d\n", pika_party[index].hp);
        printf("type:%s\n", pika_party[index].type);
        printf("attack1:%s\n", pika_party[index].attack1);
        printf("a1_power%d\n", pika_party[index].attack1_power);
        printf("a1_accurecy:%d\n", pika_party[index].attack1_accuracy);
        printf("atack2%s\n", pika_party[index].attack2);
        printf("a2_power%d\n", pika_party[index].attack2_power);
        printf("a2_accuracy:%d\n", pika_party[index].attack2_accuracy);
        printf("speed:%d\n", pika_party[index].speed);
        printf("active:%d\n", pika_party[index].active);
        index++;
        printf("\n");
    }
    *party_size = index;
    fclose(file);
}
