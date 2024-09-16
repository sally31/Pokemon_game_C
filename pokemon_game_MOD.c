#include "pokemon_game_func.h"
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

//pika's level up count
int pika_L_up = 0;



int main()
{
    srand(time(NULL));

    int party_size = 0;
    int active_size = 2;

    //Pokemon enemy_party[Num_Pokemon];

    //Pokemon pika_party[Max_Party_Size];
    
    //int enemy_party_size = 0;

    int choice_data;
    printf("do you want to use first data(1) or save data(2)");
    scanf("%d", &choice_data);

    printf("%d\n", choice_data);
    if(choice_data == 1)
    {
        printf("1");
        const char *file_enemy_party = "./output/enemy_party.csv";
        processCSV_enemy(file_enemy_party, enemy_party, &party_size, active_size);

        const char *file_pika_party = "./output/pika_party.csv";
        processCSV_pika(file_pika_party, pika_party, &party_size, active_size);
    }
    else if(choice_data == 2)
    {

        printf("2");
        const char *file_save_enemy = "./output/save_enemy.csv";
        inport_from_export_enemy_CSV(file_save_enemy, enemy_party, &party_size, active_size);

        const char *file_save_pika = "./output/save_pika.csv";
        inport_from_export_pika_CSV(file_save_pika, pika_party, &party_size, active_size);

    }

    /*
    const char *file_enemy_party = "enemy_party.csv";
    processCSV_enemy(file_enemy_party, enemy_party, &party_size, active_size);

    const char *file_pika_party = "pika_party.csv";
    processCSV_pika(file_pika_party, pika_party, &party_size, active_size);
    */

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
                    pika_party[0].hp = 5;//pika's hp became to 5
                    int save_choice;
                    printf("do you want to save this game(1)? or no(2)\n");
                    scanf("%d", &save_choice);
                    if(save_choice == 1)
                    {
                        const char *file_save_enemy = "save_enemy.csv";
                        export_enemy_CSV(file_save_enemy, enemy_party);

                        const char *file_save_pika = "save_pika.csv";
                        export_pika_CSV(file_save_pika, pika_party, pika_party_size);
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
                pika_party[pika_party_size].active = 1;

                printf("%s ,s hp became %d\n", pika_party[pika_party_size].name, pika_party[pika_party_size].hp);
                pika_party_size++;
                printf("pika_party\n");
                for(int i = 0; i < pika_party_size; i++)
                {
                    printf("%s level %d hp %d active %d\n", pika_party[i].name,
                    pika_party[i].level, pika_party[i].hp, pika_party[i].active);
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
