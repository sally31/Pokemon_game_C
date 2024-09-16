#include "pokemon_game_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define Max_Name_Len 50
#define Num_Pokemon 5

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
        char *token;
        char *rest = line;

        char name[Max_Name_Len];
        int level = 0;
        int hp = 0;

        //while((token = strtok_r(rest, ",", &rest)))
        token = strtok_r(rest, ",", &rest);
        if(token) strncpy(name, token, Max_Name_Len-1);
        name[Max_Name_Len - 1] = '\0'; 

        token = strtok_r(rest, ",", &rest);
        if(token) level = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) hp = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) active = atoi(token);
        
        enemy_party[index] = createPokemon(name, level, hp, active);
        printf("%s\n", enemy_party[index].name);
        printf("%d\n", enemy_party[index].level);
        printf("%d\n", enemy_party[index].hp);
        printf("%d\n", enemy_party[index].active);
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

    fprintf(file, "name, level, hp, active\n");

    for(int y = 0; y < Num_Pokemon; y++)
    {
        printf("name: %s\n", enemy_party[y].name);
        printf("level: %d\n", enemy_party[y].level);
        printf("hp: %d\n", enemy_party[y].hp);
        printf("active: %d\n", enemy_party[y].active);
        printf("\n");

        fprintf(file, "%s,%d,%d,%d\n", enemy_party[y].name, enemy_party[y].level,
        enemy_party[y].hp, enemy_party[y].active);
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

        //while((token = strtok_r(rest, ",", &rest)))
        token = strtok_r(rest, ",", &rest);
        if(token) strncpy(name, token, Max_Name_Len-1);
        name[Max_Name_Len - 1] = '\0'; 

        token = strtok_r(rest, ",", &rest);
        if(token) level = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) hp = atoi(token);

        token = strtok_r(rest, ",", &rest);
        if(token) active = atoi(token);
        
        enemy_party[index] = createPokemon(name, level, hp, active);
        printf("%s\n", enemy_party[index].name);
        printf("%d\n", enemy_party[index].level);
        printf("%d\n", enemy_party[index].hp);
        printf("%d\n", enemy_party[index].active);
        index++;
        printf("\n");
    }
    *party_size = index;
    fclose(file);
}