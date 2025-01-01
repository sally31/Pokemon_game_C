#include "pokemon_game_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define Max_Name_Len 50
#define Num_Pokemon 6

#define Max_Line_Len 1000
#define Max_Sqr_Len 100

void processCSV_enemy(const char *file_enemy_party, Pokemon enemy_party[], int *party_size, int active)
{

    
    //ファイルの読み込み
    FILE *file = fopen(file_enemy_party, "r");
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
        printf("%s\n", line);
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

        // token = strtok_r(rest, ",", &rest);
        // if(token) strncpy(type, token, Max_Name_Len-1);
        // type[Max_Name_Len - 1] = '\0';

        token = strtok_r(rest, ",", &rest);
        if(token) {
            printf("Parsed type token: %s\n", token);
            strncpy(type, token, Max_Name_Len-1);
        }
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
        
        enemy_party[index] = createPokemon(name, level, hp, type, 
        attack1, attack1_power, attack1_accuracy, attack2,
        attack2_power, attack2_accuracy, speed, active);
        printf("name: %s\n", enemy_party[index].name);
        printf("level: %d\n", enemy_party[index].level);
        printf("hp: %d\n", enemy_party[index].hp);
        printf("type: %s\n", enemy_party[index].type);
        printf("attack1: %s\n", enemy_party[index].attack1);
        printf("a1_power: %d\n", enemy_party[index].attack1_power);
        printf("a1_accuracy: %d\n", enemy_party[index].attack1_accuracy);
        printf("attack2: %s\n", enemy_party[index].attack2);
        printf("a2_power: %d\n", enemy_party[index].attack2_power);
        printf("a2_aqccuracy: %d\n", enemy_party[index].attack2_accuracy);
        printf("speed: %d\n", enemy_party[index].speed);
        printf("active: %d\n", enemy_party[index].active);
        index++;
        printf("\n");
    }
    *party_size = index;
    fclose(file);
}

void export_enemy_CSV(const char *file_save_enemy, Pokemon enemy_party[])
{
    //struct Pokemon enemy_party[Num_Pokemon];
    FILE *file = fopen(file_save_enemy, "w");
    if(file == NULL)
    {
        perror("can't open file");
        return;
    }

    fprintf(file, "name, level, hp, type, attack1, attack1_power, attack1_accuracy, attack2, attack2_power, attack2_accuracy, speed, active\n");

    for(int y = 0; y < Num_Pokemon; y++)
    {
        printf("name: %s\n", enemy_party[y].name);
        printf("level: %d\n", enemy_party[y].level);
        printf("hp: %d\n", enemy_party[y].hp);
        printf("type: %s\n", enemy_party[y].type);
        printf("attack1: %s\n", enemy_party[y].attack1);
        printf("attack1_power: %d\n", enemy_party[y].attack1_power);
        printf("attack1_accuracy: %d\n", enemy_party[y].attack1_accuracy);
        printf("attack2: %s\n", enemy_party[y].attack2);
        printf("attack2_power: %d\n", enemy_party[y].attack2_power);
        printf("attack2_accuracy: %d\n", enemy_party[y].attack2_accuracy);
        printf("speed: %d\n", enemy_party[y].speed);
        printf("active: %d\n", enemy_party[y].active);
        printf("\n");

        fprintf(file, "%s, %d, %d, %s, %s, %d, %d, %s, %d, %d, %d, %d\n", enemy_party[y].name, enemy_party[y].level,
        enemy_party[y].hp, enemy_party[y].type, enemy_party[y].attack1, enemy_party[y].attack1_power, enemy_party[y].attack1_accuracy,
        enemy_party[y].attack2, enemy_party[y].attack2_power, enemy_party[y].attack2_accuracy, enemy_party[y].speed, 
        enemy_party[y].active);
    }
    fclose(file);

}

/*____________________________________________________________________________*/
/*セーブしたデータを読み込む*/

void inport_from_export_enemy_CSV(const char *file_save_enemy, Pokemon enemy_party[], int *party_size, int active)
{
    //ファイルの読み込み
    FILE *file = fopen(file_save_enemy, "r");
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
        
        enemy_party[index] = createPokemon(name, level, hp, type, 
        attack1, attack1_power, attack1_accuracy, attack2,
        attack2_power, attack2_accuracy, speed,active);
        printf("%s\n", enemy_party[index].name);
        printf("%d\n", enemy_party[index].level);
        printf("%d\n", enemy_party[index].hp);
        printf("%s\n", enemy_party[index].type);
        printf("%s\n", enemy_party[index].attack1);
        printf("%d\n", enemy_party[index].attack1_power);
        printf("%d\n", enemy_party[index].attack1_accuracy);
        printf("%s\n", enemy_party[index].attack2);
        printf("%d\n", enemy_party[index].attack2_power);
        printf("%d\n", enemy_party[index].attack2_accuracy);
        printf("%d\n", enemy_party[index].speed);
        printf("%d\n", enemy_party[index].active);
        index++;
        printf("\n");
    }
    *party_size = index;
    fclose(file);
}