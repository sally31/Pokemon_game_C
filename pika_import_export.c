#include "pokemon_game_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define Max_Name_Len 50
#define Max_Party_Size 6

#define Max_Line_Len 1000
#define Max_Sqr_Len 100

Pokemon createPokemon(const char *name, int level, int hp, int active)
{
    Pokemon newPokemon;
    strcpy(newPokemon.name, name);
    newPokemon.name[Max_Name_Len - 1] = '\0'; 
    newPokemon.level = level;
    newPokemon.hp = hp;
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
        
        pika_party[index] = createPokemon(name, level, hp, active);
        printf("%s\n", pika_party[index].name);
        printf("%d\n", pika_party[index].level);
        printf("%d\n", pika_party[index].hp);
        printf("%d\n", pika_party[index].active);
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

    fprintf(file, "name, level, hp, active\n");

    for(int y = 0; y < pika_party_size; y++)
    {
        printf("name: %s\n", pika_party[y].name);
        printf("level: %d\n", pika_party[y].level);
        printf("hp: %d\n", pika_party[y].hp);
        printf("active: %d\n", pika_party[y].active);
        printf("\n");

        fprintf(file, "%s,%d,%d,%d\n", pika_party[y].name, pika_party[y].level,
        pika_party[y].hp, pika_party[y].active);
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
        
        pika_party[index] = createPokemon(name, level, hp, active);
        printf("%s\n", pika_party[index].name);
        printf("%d\n", pika_party[index].level);
        printf("%d\n", pika_party[index].hp);
        printf("%d\n", pika_party[index].active);
        index++;
        printf("\n");
    }
    *party_size = index;
    fclose(file);
}
