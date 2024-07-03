#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define enemy_max_HP 5
#define Pokemon_count 5
#define Pokemon_Max_Level 5
#define Win_HP 10
#define Max_Name_Len 50
#define Num_Pokemon 5
#define Max_Party_Size 6

#define Max_Line_Len 1000
#define Max_Sqr_Len 100


struct Pokemon
{
    char name[Max_Name_Len];
    int level;
    int hp;
    int active;
};

struct Pokemon createPokemon(const char *name, int level, int hp, int active)
{
    struct Pokemon newPokemon;
    strcpy(newPokemon.name, name);
    newPokemon.name[Max_Name_Len - 1] = '\0'; 
    newPokemon.level = level;
    newPokemon.hp = hp;
    newPokemon.active = active; 
    return newPokemon;
}


void processCSV_enemy(const char *file_enemy_party, struct Pokemon enemy_party[], int *party_size, int active)
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

void processCSV_pika(const char *file_pika_party, struct Pokemon pika_party[], int *party_size, int active)
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

void export_enemy_CSV(const char *file_save_enemy, struct Pokemon enemy_party[])
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

/*
int main()
{
    srand(time(NULL));
    //struct Pokemon party[Max_Party_Size];

    struct Pokemon enemy_party[Max_Party_Size];

    //struct Pokemon pika_party[Max_Party_Size];

    int party_size = 0;
    int active_size = 2;
    //int enemy_party_size = 0;

    const char *filename = "enemy_party.csv";
    processCSV_enemy(filename, enemy_party, &party_size, active_size);
    
    for(int i = 0; i < party_size; i++)
    {
        printf("Name: %s\n", enemy_party[i].name);
        printf("Level: %d\n", enemy_party[i].level);
        printf("HP: %d\n", enemy_party[i].hp);
        printf("active: %d\n", enemy_party[i].active);
        printf("\n");
    }

    const char *file_save_enemy = "save_enemy.csv";
    export_enemy_CSV(file_save_enemy, enemy_party);

    return 0;

}*/



//pika's level up count
int pika_L_up = 0;



int main()
{
    srand(time(NULL));
    //struct Pokemon party[Num_Pokemon];

    struct Pokemon enemy_party[Num_Pokemon];

    struct Pokemon pika_party[Max_Party_Size];
    int party_size = 0;
    int active_size = 2;
    //int enemy_party_size = 0;

    const char *file_enemy_party = "enemy_party.csv";
    processCSV_enemy(file_enemy_party, enemy_party, &party_size, active_size);

    const char *file_pika_party = "pika_party.csv";
    processCSV_pika(file_pika_party, pika_party, &party_size, active_size);

    int pika_party_size = 1;


    int choice;
    
    while(pika_party[0].hp >=0 && pika_party[0].hp<=10)
    {
        int j;
        
        do
        {
            j = rand() % Pokemon_Max_Level;
        } while (!enemy_party[j].active);


        printf("%s has appered! level %d hp %d\n", enemy_party[j].name, enemy_party[j].level, enemy_party[j].hp);
        printf("fight(1) or run away(2)\n");
        
        
        scanf("%d", &choice);
        if(choice == 1)
        {
            
             if (enemy_party[j].level >= pika_party[0].level)//ポケモンがピカチューより強かったら
            {
                printf("%s is strongger than pika! pika lost\n", enemy_party[j].name);//ポケモンはピカよりも強い！ピカの負け
                pika_party[0].hp--;//ピカのHPを１減らす
                enemy_party[j].hp++;
                if(enemy_party[j].hp == enemy_max_HP)//敵のhpがmax(5)ならlevelを１上げてhpを２に戻す
                {
                    enemy_party[j].level ++;
                    enemy_party[j].hp = 2;
                }
                printf("Pika'sHP %d\n", pika_party[0].hp);
                printf("%s's hp is 1 up\n", enemy_party[j].name);
                printf("%s's level is %d. hp is %d\n", enemy_party[j].name, enemy_party[j].level, enemy_party[j].hp);
                if (pika_party[0].hp <= 0)//HPが０より下になったら
                {
                    printf("pika's HP is 0! game over\n");//バトル終了
                    break;
                }
            }

            if (enemy_party[j].level < pika_party[0].level)//ピカの方が強かったら
            {
                printf("pika is stronger than %s. pika won!\n",enemy_party[j].name);
                pika_party[0].hp++;//HPが１増える
                enemy_party[j].hp--;//敵のHPが１減る
                pika_L_up++;
                printf("%d\n", pika_L_up);

                if(pika_L_up == 3)
                {
                    pika_party[0].level++;
                    printf("paka grew to level %d\n", pika_party[0].level);
                    pika_L_up = 0;
                }
                printf("Pika'sHP %d\n", pika_party[0].hp);
                printf("%s's HP is %d\n", enemy_party[j].name, enemy_party[j].hp);
                if (pika_party[0].hp  >= Win_HP)//ピカのHPが１０以上だったら
                {
                    printf("Pikachu won!! yaaaay!!\n");
                    int save_choice;
                    printf("do you want to save this game(1)? or no(2)\n");
                    scanf("%d", &save_choice);
                    if(save_choice == 1)
                    {
                        const char *file_save_enemy = "save_enemy.csv";
                        export_enemy_CSV(file_save_enemy, enemy_party);
                    }

                    break;
                }
            }
            if (enemy_party[j].hp == 0)//敵のhpが０になったらpartyから外れる
            {
                printf("%s's hp is 0! %s will be gone.\n", enemy_party[j].name, enemy_party[j].name);
                enemy_party[j].active = 0;
                pika_party[pika_party_size] = enemy_party[j];
                printf("%s has joined pika_party\n", pika_party[pika_party_size].name);
                pika_party[pika_party_size].hp = 3;
                printf("%s ,s hp became %d\n", pika_party[pika_party_size].name, pika_party[pika_party_size].hp);
                pika_party_size++;
                printf("pika_party\n");
                for(int i = 0; i < pika_party_size; i++)
                {
                    printf("%s level %d hp %d\n", pika_party[i].name,
                    pika_party[i].level, pika_party[i].hp);
                }

            }
            
        }
        else if(choice == 2)
        {
            //printf("choice is %d\n", choice);
            printf("pika run away\n");
        }
       
    }
    
    return 0;
}
