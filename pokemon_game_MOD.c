#include "pokemon_game_func.h"
//#include <SDL2/SDL.h>
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

int second = 3;

int pika_party_size = 1;

// int main()
// {
//      srand(time(NULL));

//     int party_size = 0;
//     int active_size = 2;
//     const char *file_enemy_party = "./output/enemy_party.csv";
//     processCSV_enemy(file_enemy_party, enemy_party, &party_size, active_size);

//     const char *file_pika_party = "./output/pika_party.csv";
//     processCSV_pika(file_pika_party, pika_party, &party_size, active_size);

//     // const char *file_save_enemy = "./output/save_enemy.csv";
//     // inport_from_export_enemy_CSV(file_save_enemy, enemy_party, &party_size, active_size);

//     // const char *file_save_pika = "./output/save_pika.csv";
//     // inport_from_export_pika_CSV(file_save_pika, pika_party, &party_size, active_size);


// }


void enemy_attack(int j, int fight_pokemon)
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
            printf("%s\n", enemy_party[j].attack1);
            printf("%s got %d damage\n", pika_party[fight_pokemon].name, enemy_party[j].attack1_power);
            pika_party[fight_pokemon].hp -= enemy_party[j].attack1_power;     
        }

        else
        {
            printf("attack missed\n");
        }
    }
    else if(r_num == 2)
    {
        if(enemy_party[j].attack2_accuracy >= probability_hit)
        {
            printf("%s\n", enemy_party[j].attack2);
            printf("%s got %d damage\n", pika_party[fight_pokemon].name, enemy_party[j].attack2_power);
            pika_party[fight_pokemon].hp -= enemy_party[j].attack2_power;     
        }

        else
        {
            printf("attack missed\n");
        }
    }
}

void pika_attack(int fight_pokemon,int j)
{
    srand(time(NULL));
    int probability_hit = rand() % 100+1;
    printf("%d\n", probability_hit);
    int attack_choice_pika;

    printf("%s's turn\n", pika_party[fight_pokemon].name);
    printf("which move do you want to use?(1)attack:%s, damege:%d, accurecy:%d or (2)attack:%s, damege:%d, accurecy:%d\n",
    pika_party[fight_pokemon].attack1, pika_party[fight_pokemon].attack1_power, 
    pika_party[fight_pokemon].attack1_accuracy, pika_party[fight_pokemon].attack2,
    pika_party[fight_pokemon].attack2_power, pika_party[fight_pokemon].attack2_accuracy);
    scanf("%d", &attack_choice_pika);
    
    if(attack_choice_pika == 1)
    {
        if(pika_party[fight_pokemon].attack1_accuracy >= probability_hit)
        {
            printf("%s\n", pika_party[fight_pokemon].attack1);
            printf("%s got %d damage\n", enemy_party[j].name, pika_party[fight_pokemon].attack1_power);
            enemy_party[j].hp -= pika_party[fight_pokemon].attack1_power;
            
        }
        else
        {
            printf("attack missed\n");
        }

    }
    else if(attack_choice_pika == 2)
    {
        if(pika_party[fight_pokemon].attack1_accuracy >= probability_hit)
        {
            printf("%s\n", pika_party[fight_pokemon].attack2);
            printf("%s got %d damage\n", enemy_party[j].name, pika_party[fight_pokemon].attack2_power);
            enemy_party[j].hp -= pika_party[fight_pokemon].attack2_power;
            
        }
        else
        {
            printf("attack missed\n");
        }
    }
}


int main()
{
    srand(time(NULL));

    int party_size = 0;
    int active_size = 2;

    int choice_data;
    printf("do you want to use first data(1) or save data(2)\n");
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

    
    int fight_pokemon = 0;
    int pika_active_number = pika_party_size;
    int enemy_active_number = 6;
    
    while(pika_active_number != 0 || enemy_active_number != 0)
    {
        //pick the random ememy pikomon
        int j;
        do
        {
            j = rand() % Pokemon_Max_Level;
        } while (!enemy_party[j].active);


        printf("%s has appered! level %d hp %d\n", enemy_party[j].name, enemy_party[j].level, enemy_party[j].hp);
        printf("fight(3) or run away(4)\n");
        
        int choice;
        scanf("%d", &choice);
        if(choice == 3)
        {
            //change pokemon if pika_party has more then 1 pokemon
            if(pika_party_size > 1)
            {
                int change_pika_party;
                printf("Do you want to change pokemon?\n");
                for(int i=0; i < pika_party_size; i++)
                {
                    printf("%d:%s\n", i, pika_party[i].name);
                    
                }
                do
                {
                    printf("press number\n");
                    scanf("%d", &change_pika_party);
                }while(pika_party[change_pika_party].hp <=0);
                
                fight_pokemon = change_pika_party;
            }
            
            while(pika_party[fight_pokemon].hp >=0 || enemy_party[j].hp >=0)//until one of them win
            {
                //int attack_choice_enemy;
                
                if (enemy_party[j].speed > pika_party[fight_pokemon].speed)//ememy is stronger then pika_party
                {
                    printf("%s attacked %s\n", enemy_party[j].name, pika_party[fight_pokemon].name);
                    sleep(second);
                    int temp_enemy_a1_power = enemy_party[j].attack1_power;
                    int temp_enemy_a2_power = enemy_party[j].attack2_power;
                    printf("t_e_a1_p:%d t_e_a2_p:%d\n", temp_enemy_a1_power, temp_enemy_a2_power);

                    type_pokemon_enemy_attack(enemy_party, pika_party, j, fight_pokemon);
                    sleep(second);
                    enemy_attack(j, fight_pokemon);

                    enemy_party[j].attack1_power = temp_enemy_a1_power;
                    enemy_party[j].attack2_power = temp_enemy_a2_power;
                    printf("e_a1_p:%d w_a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);


                    if(pika_party[fight_pokemon].hp <= 0)
                    {
                        printf("%s's hp is 0. %s lost\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name);
                        break;
                    }
                    else
                    {
                        printf("%s's hp is %d\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
                    }
                    sleep(second);

                    printf("%s's turn. %s attacked %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name, enemy_party[j].name);
                    int temp_pika_a1_power = pika_party[fight_pokemon].attack1_power;
                    int temp_pika_a2_power = pika_party[fight_pokemon].attack2_power;
                    printf("t_p_a1_p:%d t_p_a2_p:%d\n", temp_pika_a1_power, temp_pika_a2_power);

                    type_pokemon_pika_attack(enemy_party, pika_party, j, fight_pokemon);
                    sleep(second);
                    pika_attack(fight_pokemon, j);

                    pika_party[fight_pokemon].attack1_power = temp_pika_a1_power;
                    pika_party[fight_pokemon].attack2_power = temp_pika_a2_power;
                    printf("p_a1_p:%d p_a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);

                    

                    if(enemy_party[j].hp <= 0)
                    {
                        printf("%s's hp is 0. %s lost\n", enemy_party[j].name, enemy_party[j].name);
                        break;
                    }
                    else
                    {
                        printf("%s's hp is %d\n", enemy_party[j].name, enemy_party[j].hp);
                    }
                    sleep(second);
                }
                //pika is stronger then ememy
                else if(pika_party[fight_pokemon].speed > enemy_party[j].speed )
                {
                    int temp_pika_a1_power = pika_party[fight_pokemon].attack1_power;
                    int temp_pika_a2_power = pika_party[fight_pokemon].attack2_power;
                    printf("t_p_a1_p:%d t_p_a2_p:%d\n", temp_pika_a1_power, temp_pika_a2_power);

                    type_pokemon_pika_attack(enemy_party, pika_party, j, fight_pokemon);
                    sleep(second);
                    pika_attack(fight_pokemon, j);

                    pika_party[fight_pokemon].attack1_power = temp_pika_a1_power;
                    pika_party[fight_pokemon].attack2_power = temp_pika_a2_power;
                    printf("p_a1_p:%d p_a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);


                    if(enemy_party[j].hp <= 0)
                    {
                        printf("%s's hp is 0. %s lost\n", enemy_party[j].name, enemy_party[j].name);
                        break;
                    }
                    else
                    {
                        printf("%s's hp is %d\n", enemy_party[j].name, enemy_party[j].hp);
                    }
                    
                    sleep(second);

                    printf("%s's turn. %s attacked %s\n", enemy_party[j].name, enemy_party[j].name, pika_party[fight_pokemon].name);
                    sleep(second);
                    int temp_enemy_a1_power = enemy_party[j].attack1_power;
                    int temp_enemy_a2_power = enemy_party[j].attack2_power;
                    printf("t_e_a1_p:%d t_e_a2_p:%d\n", temp_enemy_a1_power, temp_enemy_a2_power);

                    type_pokemon_enemy_attack(enemy_party, pika_party, j, fight_pokemon);
                    sleep(second);
                    enemy_attack(j, fight_pokemon);

                    enemy_party[j].attack1_power = temp_enemy_a1_power;
                    enemy_party[j].attack2_power = temp_enemy_a2_power;
                    printf("e_a1_p:%d w_a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);


                    if(pika_party[fight_pokemon].hp <= 0)
                    {
                        printf("%s's hp is 0. %s lost\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name);
                        break;
                    }
                    else
                    {
                        printf("%s's hp is %d\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
                    }
                    sleep(second);
                }
            }
            //ここまで新しく書いた所24/11/2024//

            if (enemy_party[j].hp <= 0)//敵のhpが０になったらpartyから外れる
            {
                sleep(second);
                printf("%s's hp is 0! %s will be gone.\n", enemy_party[j].name, enemy_party[j].name);
                enemy_party[j].active = 0;
                enemy_active_number --;
                pika_party[pika_party_size] = enemy_party[j];
                printf("%s has joined pika_party\n", pika_party[pika_party_size].name);
                pika_party[pika_party_size].hp = 150;
                pika_party[pika_party_size].active = 1;
                 pika_active_number ++;

                printf("%s ,s hp became %d\n", pika_party[pika_party_size].name, pika_party[pika_party_size].hp);
                pika_party_size++;
                printf("pika_party\n");
                for(int i = 0; i < pika_party_size; i++)
                {
                    printf("name:%s level:%d hp:%d active:%d\n", pika_party[i].name,
                    pika_party[i].level, pika_party[i].hp, pika_party[i].active);
                }

            }

            if(pika_party[fight_pokemon].hp <= 0)
            {
                pika_party[fight_pokemon].active = 0;
                pika_active_number --;

            }
             
           

           
            int save_choice;
            printf("do you want to save this game and finish(1)? or continue(2)\n");
            scanf("%d", &save_choice);
            if(save_choice == 1)
            {
                const char *file_save_enemy = "save_enemy.csv";
                export_enemy_CSV(file_save_enemy, enemy_party);
                printf("hello\n");

                const char *file_save_pika = "save_pika.csv";
                export_pika_CSV(file_save_pika, pika_party, pika_party_size);
                break;
            }

            else if(save_choice == 2)
            {
                if(pika_active_number == 0)
                {
                    printf("pika party have lost!! SAD!!!\n");
                    break;
                }
                else if(enemy_active_number == 0)
                {
                    printf("enemy party have lost!! pika party won! yaaay!!!\n");
                    break;
                }
                else
                {
                    continue;
                }
            }
            
            
        }
        else if(choice == 4)
        {
            //printf("choice is %d\n", choice);
            printf("pika run away\n");
        }
       
    }
    
    return 0;
}

// #include "pokemon_game_func.h"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <unistd.h>

// #define enemy_max_HP 5
// #define Pokemon_count 5
// #define Pokemon_Max_Level 6
// #define Win_HP 10
// #define Max_Name_Len 50
// #define Num_Pokemon 6
// #define Max_Party_Size 6

// #define Max_Line_Len 1000
// #define Max_Sqr_Len 100

// int second = 5;
// int pika_party_size = 1;
// char buffer[200];
// char message_enemy_attack[][200];
// char message_pika_attack[][200];

// // HPバーを描画する関数
// void renderHPBarpika(SDL_Renderer* renderer, int x, int y, int width, int height, int currentHP, int maxHP) {
//     // 背景のバー（灰色）
//     SDL_Rect bgRect = {x, y, width, height};
//     SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // 背景色（灰色）
//     SDL_RenderFillRect(renderer, &bgRect);

//     // HPのバー（緑色）
//     SDL_Rect hpRect = {x, y, (int)((float)currentHP / maxHP * width), height};
//     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // 緑色
//     SDL_RenderFillRect(renderer, &hpRect);
// }

// void renderHPBarenemy(SDL_Renderer* renderer, int x, int y, int width, int height, int currentHP, int maxHP) {
//     // 背景のバー（灰色）
//     SDL_Rect bgRect = {x, y, width, height};
//     SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // 背景色（灰色）
//     SDL_RenderFillRect(renderer, &bgRect);

//     // HPのバー（緑色）
//     SDL_Rect hpRect = {x, y, (int)((float)currentHP / maxHP * width), height};
//     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // 緑色
//     SDL_RenderFillRect(renderer, &hpRect);
// }

// // テキストを描画する関数
// void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
//     SDL_Color textColor = {255, 255, 255, 255}; // 白色
//     SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
//     if (!textSurface) {
//         fprintf(stderr, "Failed to render text: %s\n", TTF_GetError());
//         return;
//     }

//     SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//     if (!textTexture) {
//         fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
//         SDL_FreeSurface(textSurface);
//         return;
//     }

//     SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
//     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set to white
//     SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

//     SDL_FreeSurface(textSurface);
//     SDL_DestroyTexture(textTexture);
// }

// int clearTextArea(SDL_Renderer* renderer, int x, int y, int w, int h, int blend, int r, int g, int b) {
//     // 背景色（黒）で塗りつぶす
//     SDL_Rect clearRect;
//     SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//     clearRect.x = x;
//     clearRect.y = y;
//     clearRect.w = w;
//     clearRect.h = h;

//     SDL_SetRenderDrawColor(renderer, r, g, b, blend);
//     SDL_RenderFillRect(renderer, &clearRect); // 黒で塗りつぶし
//     //SDL_RenderPresent(renderer);

//     return 0;
// }

// //enemy_party_attack
// int enemy_attack(int j, int fight_pokemon, char message_enemy_attack[][200])
// {
//     srand(time(NULL));
//     int r_num = rand() % 2+1;
//     printf("r_num:%d\n", r_num);

//     int probability_hit = rand() % 100+1;
//     printf("probability_hit:%d\n", probability_hit);

//     if(r_num == 1)
//     {
//         if(enemy_party[j].attack1_accuracy >= probability_hit)
//         {
//             sprintf(message_enemy_attack[0], "%s\n", enemy_party[j].attack1);
//             printf("%s\n", enemy_party[j].attack1);
//             sprintf(message_enemy_attack[1], "%s got %d damage\n", pika_party[fight_pokemon].name, enemy_party[j].attack1_power);
//             printf("%s got %d damage\n", pika_party[fight_pokemon].name, enemy_party[j].attack1_power);
//             pika_party[fight_pokemon].hp -= enemy_party[j].attack1_power;
//             return 1;     
//         }

//         else
//         {
//             sprintf(message_enemy_attack[2], "attack missed\n");
//             printf("attack missed\n");
//             return 2;
//         }
//     }
//     else if(r_num == 2)
//     {
//         if(enemy_party[j].attack2_accuracy >= probability_hit)
//         {
//             sprintf(message_enemy_attack[0], "%s\n", enemy_party[j].attack2);
//             printf("%s\n", enemy_party[j].attack2);
//             sprintf(message_enemy_attack[1], "%s got %d damage\n", pika_party[fight_pokemon].name, enemy_party[j].attack2_power);
//             printf("%s got %d damage\n", pika_party[fight_pokemon].name, enemy_party[j].attack2_power);
//             pika_party[fight_pokemon].hp -= enemy_party[j].attack2_power;  
//             return 1;   
//         }

//         else
//         {
//             sprintf(message_enemy_attack[2], "attack missed\n");
//             printf("attack missed\n");
//             return 2;
//         }
//     }
// }

// //pika_party_attack
// int pika_attack(int fight_pokemon,int j, char message_pika_attack[][200], int attack_choice_pika)
// {

//     srand(time(NULL));
//     int probability_hit = rand() % 100+1;
//     printf("%d\n", probability_hit);

    
//     if(attack_choice_pika == 1)
//     {
//         if(pika_party[fight_pokemon].attack1_accuracy >= probability_hit)
//         {
//             sprintf(message_pika_attack[2], "%s\n", pika_party[fight_pokemon].attack1);
//             sprintf(message_pika_attack[3], "%s got %d damage\n", enemy_party[j].name, pika_party[fight_pokemon].attack1_power);
//             printf("%s\n", pika_party[fight_pokemon].attack1);
//             printf("%s got %d damage\n", enemy_party[j].name, pika_party[fight_pokemon].attack1_power);
//             enemy_party[j].hp -= pika_party[fight_pokemon].attack1_power;
//             return 1;
            
//         }
//         else
//         {
//             sprintf(message_pika_attack[4], "attack missed\n");
//             printf("attack missed\n");
//             return 2;
//         }

//     }
//     else if(attack_choice_pika == 2)
//     {
//         if(pika_party[fight_pokemon].attack1_accuracy >= probability_hit)
//         {
//             sprintf(message_pika_attack[2], "%s\n", pika_party[fight_pokemon].attack2);
//             sprintf(message_pika_attack[3], "%s got %d damage\n", enemy_party[j].name, pika_party[fight_pokemon].attack2_power);
//             printf("%s\n", pika_party[fight_pokemon].attack2);
//             printf("%s got %d damage\n", enemy_party[j].name, pika_party[fight_pokemon].attack2_power);
//             enemy_party[j].hp -= pika_party[fight_pokemon].attack2_power;
//             return 1;
            
//         }
//         else
//         {
//             sprintf(message_pika_attack[4], "attack missed\n");
//             printf("attack missed\n");
//             return 2;
//         }
//     }
// }


// int main() 
// {
//     srand(time(NULL));

//     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//         fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
//         return 1;
//     }
//     if (TTF_Init() == -1) {
//         fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
//         SDL_Quit();
//         return 1;
//     }

//     SDL_Window* window = SDL_CreateWindow("battle scene", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
//     if (!window) {
//         fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
//         TTF_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     if (!renderer) {
//         fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
//         SDL_DestroyWindow(window);
//         TTF_Quit();
//         SDL_Quit();
//         return 1;
//     }

//     TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 24);
//     if (!font) {
//         fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
//         SDL_DestroyRenderer(renderer);
//         SDL_DestroyWindow(window);
//         TTF_Quit();
//         SDL_Quit();
//         return 1;
//     }


//     int currentHP = 70;
//     int maxHP = 100;

//     SDL_Event e;
//     int quit = 0;

//     // 画面をクリア
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//     SDL_RenderClear(renderer);
//     int party_size = 0;
//     int active_size = 2;

//     int choice_data;
//     renderText(renderer, font, "do you want to use first data(1) or save data(2)", 50, 550);
//     SDL_RenderPresent(renderer);//スクリーン反映
//     printf("do you want to use first data(1) or save data(2)\n");//word1
//     scanf("%d", &choice_data);


//     printf("%d\n", choice_data);
//         if(choice_data == 1)
//     {
//         printf("1");
//         const char *file_enemy_party = "./output/enemy_party.csv";
//         processCSV_enemy(file_enemy_party, enemy_party, &party_size, active_size);

//         const char *file_pika_party = "./output/pika_party.csv";
//         processCSV_pika(file_pika_party, pika_party, &party_size, active_size);
//     }
//     else if(choice_data == 2)
//     {

//         printf("2");
//         const char *file_save_enemy = "./output/save_enemy.csv";
//         inport_from_export_enemy_CSV(file_save_enemy, enemy_party, &party_size, active_size);

//         const char *file_save_pika = "./output/save_pika.csv";
//         inport_from_export_pika_CSV(file_save_pika, pika_party, &party_size, active_size);

//     }
//     int fight_pokemon = 0;
//     int pika_active_number = pika_party_size;
//     int enemy_active_number = 6;
    
//     char messages[2][256];

//     while (!quit || pika_active_number != 0 || enemy_active_number != 0) 
//     {
//         while (SDL_PollEvent(&e)) 
//         {
//             if (e.type == SDL_QUIT)
//              {
//                 quit = 1;
//             }
//         }


//          //pick the random ememy pikomon
//         int j;
//         do
//         {
//             j = rand() % Pokemon_Max_Level;
//         } while (!enemy_party[j].active);
        
//         // HPバーの描画enemy
//         snprintf(buffer, sizeof(buffer), "%s  :%d/150", enemy_party[j].name, enemy_party[j].hp);
//         renderText(renderer, font, buffer, 450, 10);
//         renderHPBarenemy(renderer, 400, 50, 300, 30, enemy_party[j].hp, maxHP);
//         // HPバーの描画pika
//         snprintf(buffer, sizeof(buffer), "%s  :%d/150", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//         renderText(renderer, font, buffer, 50, 300);
//         renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

//         //word1の文字を消す        
//         clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);

//         //変数の出力
//         snprintf(buffer, sizeof(buffer), "%s has appered! level %d hp %d", enemy_party[j].name, enemy_party[j].level, enemy_party[j].hp);
//         renderText(renderer, font, buffer, 50, 500);
//         printf("%s has appered! level %d hp %d\n", enemy_party[j].name, enemy_party[j].level, enemy_party[j].hp);
//         renderText(renderer, font, "fight(1) or run away(2)", 50, 550);
//         printf("fight(1) or run away(2)\n");
//         /*ここまで追加した上*/
//         SDL_RenderPresent(renderer);

//         int choice;
//         scanf("%d", &choice);
//         if(choice == 1)
//         {
//             //change pokemon if pika_party has more then 1 pokemon
//             if(pika_party_size > 1)
//             {
//                 clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
//                 clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
//                 int change_pika_party;
//                 renderText(renderer, font, "Do you want to change pokemon", 50, 400);
                
//                 for(int i=0; i < pika_party_size; i++)
//                 {
//                     printf("%d:%s\n", i, pika_party[i].name);
                    
//                 }
//                 do
//                 {
//                     printf("press number\n");
//                     scanf("%d", &change_pika_party);
//                 }while(pika_party[change_pika_party].hp <=0);
                
//                 fight_pokemon = change_pika_party;
//             }
//             while(pika_party[fight_pokemon].hp >=0 || enemy_party[j].hp >=0)//until one of them win
//             {
//                 //int attack_choice_enemy;
                
//                 if (enemy_party[j].speed > pika_party[fight_pokemon].speed)//ememy is stronger then pika_party
//                 {
//                     clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
//                     // HPバーの描画enemy
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", enemy_party[j].name, enemy_party[j].hp);
//                     renderText(renderer, font, buffer, 450, 10);
//                     renderHPBarenemy(renderer, 400, 50, 300, 30, enemy_party[j].hp, maxHP);
//                     // HPバーの描画pika
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//                     renderText(renderer, font, buffer, 50, 300);
//                     renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

//                     snprintf(buffer, sizeof(buffer), "%s attacked %s", enemy_party[j].name, pika_party[fight_pokemon].name);
//                     renderText(renderer, font, buffer, 50, 400);
//                     //SDL_RenderPresent(renderer);
//                     sleep(second);
//                     int temp_enemy_a1_power = enemy_party[j].attack1_power;
//                     int temp_enemy_a2_power = enemy_party[j].attack2_power;
//                     printf("t_e_a1_p:%d t_e_a2_p:%d\n", temp_enemy_a1_power, temp_enemy_a2_power);

//                     type_pokemon_enemy_attack(enemy_party, pika_party, j, fight_pokemon, messages);
//                     renderText(renderer, font, messages[0], 50, 450);
//                     renderText(renderer, font, messages[1], 50, 500);
//                     SDL_RenderPresent(renderer);
//                     sleep(second);
//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);
                    
//                     int enemy_index = enemy_attack(j, fight_pokemon, message_enemy_attack);
//                     if(enemy_index == 1)
//                     {
//                         renderText(renderer, font, message_enemy_attack[0], 50, 400);
//                         renderText(renderer, font, message_enemy_attack[1], 50, 450);
//                     }
//                     else if(enemy_index == 2)
//                     {
//                         renderText(renderer, font, message_enemy_attack[2], 50, 400);
//                     }
//                     //pikaが攻撃されたからpikaのhpの所だけ消す
//                     clearTextArea(renderer, 50, 300, 500, 30, 255, 0, 0, 0);
//                     // HPバーの描画enemy
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", enemy_party[j].name, enemy_party[j].hp);
//                     renderText(renderer, font, buffer, 450, 10);
//                     renderHPBarenemy(renderer, 400, 50, 300, 30, enemy_party[j].hp, maxHP);
//                     // HPバーの描画pika
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//                     renderText(renderer, font, buffer, 50, 300);
//                     renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

//                     SDL_RenderPresent(renderer);

//                     enemy_party[j].attack1_power = temp_enemy_a1_power;
//                     enemy_party[j].attack2_power = temp_enemy_a2_power;
//                     printf("e_a1_p:%d w_a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);

//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);
//                     if(pika_party[fight_pokemon].hp <= 0)
//                     {
//                         snprintf(buffer, sizeof(buffer), "%s's hp is 0. %s lost\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name);
//                         printf("%s's hp is 0. %s lost\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name);
//                         renderText(renderer, font, buffer, 50, 400);
//                         SDL_RenderPresent(renderer);
//                         clearTextArea(renderer, 50, 300, 500, 30, 255, 0, 0, 0);
//                         clearTextArea(renderer, 450, 10, 500, 30, 255, 0, 0, 0);
//                         break;
//                     }
//                     else
//                     {
//                         snprintf(buffer, sizeof(buffer), "%s's hp is %d\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//                         printf("%s's hp is %d\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//                         renderText(renderer, font, buffer, 50, 400);
//                         SDL_RenderPresent(renderer);
//                     }
//                     sleep(second);

//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);
//                     snprintf(buffer, sizeof(buffer), "%s's turn. %s attacked %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name, enemy_party[j].name);
//                     renderText(renderer, font, buffer, 50, 400);
//                     printf("%s's turn. %s attacked %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name, enemy_party[j].name);
//                     int temp_pika_a1_power = pika_party[fight_pokemon].attack1_power;
//                     int temp_pika_a2_power = pika_party[fight_pokemon].attack2_power;
//                     printf("t_p_a1_p:%d t_p_a2_p:%d\n", temp_pika_a1_power, temp_pika_a2_power);

//                     type_pokemon_pika_attack(enemy_party, pika_party, j, fight_pokemon, messages);
//                     renderText(renderer, font, messages[0], 50, 450);
//                     renderText(renderer, font, messages[1], 50, 500);
//                     SDL_RenderPresent(renderer);
//                     sleep(second);

//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);
//                     int attack_choice_pika;

//                     snprintf(buffer, sizeof(buffer), "%s's turn\n", pika_party[fight_pokemon].name);
//                     printf("%s's turn\n", pika_party[fight_pokemon].name);
//                     renderText(renderer, font, buffer, 50, 400);

//                     renderText(renderer, font, "which move do you want to use?(1) or (2)", 50, 450);
//                     snprintf(buffer, sizeof(buffer), "(1)attack:%s, damege:%d, accurecy:%d",
//                     pika_party[fight_pokemon].attack1, pika_party[fight_pokemon].attack1_power, 
//                     pika_party[fight_pokemon].attack1_accuracy);
//                     renderText(renderer, font, buffer, 50, 500);
//                     snprintf(buffer, sizeof(buffer), "(2)attack:%s, damege:%d, accurecy:%d",
//                     pika_party[fight_pokemon].attack2, pika_party[fight_pokemon].attack2_power, 
//                     pika_party[fight_pokemon].attack2_accuracy);
//                     renderText(renderer, font, buffer, 50, 550);
//                     printf("which move do you want to use?(1)attack:%s, damege:%d, accurecy:%d or (2)attack:%s, damege:%d, accurecy:%d\n",
//                     pika_party[fight_pokemon].attack1, pika_party[fight_pokemon].attack1_power, 
//                     pika_party[fight_pokemon].attack1_accuracy, pika_party[fight_pokemon].attack2,
//                     pika_party[fight_pokemon].attack2_power, pika_party[fight_pokemon].attack2_accuracy);
                    
//                     SDL_RenderPresent(renderer);
//                     scanf("%d", &attack_choice_pika);


//                     int pika_index = pika_attack(fight_pokemon, j, message_pika_attack, attack_choice_pika);
//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 550, 500, 30, 255, 0, 0, 0);
//                     if(pika_index == 1)
//                     {
//                         renderText(renderer, font, message_pika_attack[2], 50, 400);
//                         renderText(renderer, font, message_pika_attack[3], 50, 450);
//                     }
//                     else if(pika_index == 2)
//                     {
//                         renderText(renderer, font, message_pika_attack[4], 50, 400);
//                     }
//                     //enemyが攻撃されるからenemyのhpの所だけ消す
//                     clearTextArea(renderer, 400, 50, 900, 30, 255, 0, 0, 0);
//                     // HPバーの描画enemy
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", enemy_party[j].name, enemy_party[j].hp);
//                     renderText(renderer, font, buffer, 450, 10);
//                     renderHPBarenemy(renderer, 400, 50, 300, 30, enemy_party[j].hp, maxHP);
//                     // HPバーの描画pika
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//                     renderText(renderer, font, buffer, 50, 300);
//                     renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

//                     SDL_RenderPresent(renderer);
//                     pika_party[fight_pokemon].attack1_power = temp_pika_a1_power;
//                     pika_party[fight_pokemon].attack2_power = temp_pika_a2_power;
//                     printf("p_a1_p:%d p_a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);

                    

//                     if(enemy_party[j].hp <= 0)
//                     {
//                         snprintf(buffer, sizeof(buffer), "%s's hp is 0. %s lost\n", enemy_party[j].name, enemy_party[j].name);
//                         printf("%s's hp is 0. %s lost\n", enemy_party[j].name, enemy_party[j].name);
//                         renderText(renderer, font, buffer, 50, 500);
//                         SDL_RenderPresent(renderer);
//                         clearTextArea(renderer, 400, 50, 900, 30, 255, 0, 0, 0);
//                         break;
//                     }
//                     else
//                     {
//                         snprintf(buffer, sizeof(buffer), "%s's hp is %d\n", enemy_party[j].name, enemy_party[j].hp);
//                         printf("%s's hp is %d\n", enemy_party[j].name, enemy_party[j].hp);
//                         renderText(renderer, font, buffer, 50, 500);
//                     }
//                     sleep(second);
//                 }
// //************************************************************************************************
//                 //pika is stronger then ememy
//                 else if(pika_party[fight_pokemon].speed > enemy_party[j].speed )
//                 {
//                     clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
//                     // HPバーの描画enemy
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", enemy_party[j].name, enemy_party[j].hp);
//                     renderText(renderer, font, buffer, 450, 10);
//                     renderHPBarenemy(renderer, 400, 50, 300, 30, enemy_party[j].hp, maxHP);
//                     // HPバーの描画pika
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//                     renderText(renderer, font, buffer, 50, 300);
//                     renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

//                     snprintf(buffer, sizeof(buffer), "%s attacked %s", pika_party[fight_pokemon].name, enemy_party[j].name);
//                     renderText(renderer, font, buffer, 50, 400);
//                     //SDL_RenderPresent(renderer);
//                     int temp_pika_a1_power = pika_party[fight_pokemon].attack1_power;
//                     int temp_pika_a2_power = pika_party[fight_pokemon].attack2_power;
//                     printf("t_p_a1_p:%d t_p_a2_p:%d\n", temp_pika_a1_power, temp_pika_a2_power);

//                     type_pokemon_pika_attack(enemy_party, pika_party, j, fight_pokemon, messages);
//                     renderText(renderer, font, messages[0], 50, 450);
//                     renderText(renderer, font, messages[1], 50, 500);
//                     SDL_RenderPresent(renderer);
//                     sleep(second);
//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);

//                     int attack_choice_pika;

//                     snprintf(buffer, sizeof(buffer), "%s's turn\n", pika_party[fight_pokemon].name);
//                     printf("%s's turn\n", pika_party[fight_pokemon].name);
//                     renderText(renderer, font, buffer, 50, 400);

//                     renderText(renderer, font, "which move do you want to use?(1)or(2)", 50, 450);
//                     snprintf(buffer, sizeof(buffer), "(1)attack:%s, damege:%d, accurecy:%d",
//                     pika_party[fight_pokemon].attack1, pika_party[fight_pokemon].attack1_power, 
//                     pika_party[fight_pokemon].attack1_accuracy);
//                     renderText(renderer, font, buffer, 50, 500);
//                     snprintf(buffer, sizeof(buffer), "(2)attack:%s, damege:%d, accurecy:%d", pika_party[fight_pokemon].attack2,
//                     pika_party[fight_pokemon].attack2_power, pika_party[fight_pokemon].attack2_accuracy);
//                     renderText(renderer, font, buffer, 50, 550);
//                     printf("which move do you want to use?(1)attack:%s, damege:%d, accurecy:%d or (2)attack:%s, damege:%d, accurecy:%d\n",
//                     pika_party[fight_pokemon].attack1, pika_party[fight_pokemon].attack1_power, 
//                     pika_party[fight_pokemon].attack1_accuracy, pika_party[fight_pokemon].attack2,
//                     pika_party[fight_pokemon].attack2_power, pika_party[fight_pokemon].attack2_accuracy);
                    
//                     SDL_RenderPresent(renderer);
//                     scanf("%d", &attack_choice_pika);

//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 550, 500, 30, 255, 0, 0, 0);
//                     int pika_index = pika_attack(fight_pokemon, j, message_pika_attack, attack_choice_pika);
//                     if(pika_index == 1)
//                     {
//                         renderText(renderer, font, message_pika_attack[2], 50, 400);
//                         renderText(renderer, font, message_pika_attack[3], 50, 450);
//                     }
//                     else if(pika_index == 2)
//                     {
//                         renderText(renderer, font, message_pika_attack[4], 50, 400);
//                     }
//                     //enemyが攻撃されるからenemyのhpの所だけ消す
//                     clearTextArea(renderer, 400, 50, 900, 30, 255, 0, 0, 0);
//                     // HPバーの描画enemy
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", enemy_party[j].name, enemy_party[j].hp);
//                     renderText(renderer, font, buffer, 450, 10);
//                     renderHPBarenemy(renderer, 400, 50, 300, 30, enemy_party[j].hp, maxHP);
//                     // HPバーの描画pika
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//                     renderText(renderer, font, buffer, 50, 300);
//                     renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

//                     SDL_RenderPresent(renderer);

//                     pika_party[fight_pokemon].attack1_power = temp_pika_a1_power;
//                     pika_party[fight_pokemon].attack2_power = temp_pika_a2_power;
//                     printf("p_a1_p:%d p_a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);

//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);

//                     if(enemy_party[j].hp <= 0)
//                     {
//                         snprintf(buffer, sizeof(buffer), "%s's hp is 0. %s lost\n", enemy_party[j].name, enemy_party[j].name);
//                         printf("%s's hp is 0. %s lost\n", enemy_party[j].name, enemy_party[j].name);
//                         renderText(renderer, font, buffer, 50, 500);
//                         SDL_RenderPresent(renderer);
//                         clearTextArea(renderer, 400, 50, 900, 30, 255, 0, 0, 0);
//                         break;
//                     }
//                     else
//                     {
//                         snprintf(buffer, sizeof(buffer), "%s's hp is %d\n", enemy_party[j].name, enemy_party[j].hp);
//                         printf("%s's hp is %d\n", enemy_party[j].name, enemy_party[j].hp);
//                         renderText(renderer, font, buffer, 50, 500);
//                         SDL_RenderPresent(renderer);
//                     }
                    
//                     sleep(second);
//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);

//                     snprintf(buffer, sizeof(buffer), "%s's turn. %s attacked %s\n", enemy_party[j].name, enemy_party[j].name, pika_party[fight_pokemon].name);
//                     printf("%s's turn. %s attacked %s\n", enemy_party[j].name, enemy_party[j].name, pika_party[fight_pokemon].name);
//                     renderText(renderer, font, buffer, 50, 400);
//                     sleep(second);
//                     int temp_enemy_a1_power = enemy_party[j].attack1_power;
//                     int temp_enemy_a2_power = enemy_party[j].attack2_power;
//                     printf("t_e_a1_p:%d t_e_a2_p:%d\n", temp_enemy_a1_power, temp_enemy_a2_power);

//                     type_pokemon_enemy_attack(enemy_party, pika_party, j, fight_pokemon, messages);
//                     renderText(renderer, font, messages[0], 50, 450);
//                     renderText(renderer, font, messages[1], 50, 500);
//                     SDL_RenderPresent(renderer);
//                     sleep(second);
//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);

//                     int enemy_index = enemy_attack(j, fight_pokemon, message_enemy_attack);
//                     if(enemy_index == 1)
//                     {
//                         renderText(renderer, font, message_enemy_attack[0], 50, 400);
//                         renderText(renderer, font, message_enemy_attack[1], 50, 450);
//                     }
//                     else if(enemy_index == 2)
//                     {
//                         renderText(renderer, font, message_enemy_attack[2], 50, 400);
//                     }
//                     //pikaが攻撃されたからpikaのhpの所だけ消す
//                     clearTextArea(renderer, 50, 300, 500, 30, 255, 0, 0, 0);
//                     // HPバーの描画enemy
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", enemy_party[j].name, enemy_party[j].hp);
//                     renderText(renderer, font, buffer, 450, 10);
//                     renderHPBarenemy(renderer, 400, 50, 300, 30, enemy_party[j].hp, maxHP);
//                     // HPバーの描画pika
//                     snprintf(buffer, sizeof(buffer), "%s  :%d/150", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//                     renderText(renderer, font, buffer, 50, 300);
//                     renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

//                     SDL_RenderPresent(renderer);

//                     enemy_party[j].attack1_power = temp_enemy_a1_power;
//                     enemy_party[j].attack2_power = temp_enemy_a2_power;
//                     printf("e_a1_p:%d w_a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);


//                     if(pika_party[fight_pokemon].hp <= 0)
//                     {
//                         snprintf(buffer, sizeof(buffer), "%s's hp is 0. %s lost\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name);
//                         printf("%s's hp is 0. %s lost\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name);
//                         renderText(renderer, font, buffer, 50, 500);
//                         SDL_RenderPresent(renderer);
//                         clearTextArea(renderer, 50, 300, 500, 30, 255, 0, 0, 0);
//                         break;
//                     }
//                     else
//                     {
//                         snprintf(buffer, sizeof(buffer), "%s's hp is %d\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//                         printf("%s's hp is %d\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
//                         renderText(renderer, font, buffer, 50, 500);
//                     }
//                     sleep(second);
//                     clearTextArea(renderer, 50, 400, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 450, 500, 30, 255, 0, 0, 0);
//                     clearTextArea(renderer, 50, 500, 500, 30, 255, 0, 0, 0);
//                 }
//             }


        

        

//         }
//         /*
//         // Render initial text
//         renderText(renderer, font, "pikemon is fighting.", 50, 550);
//         printf("1\n");
//         SDL_RenderPresent(renderer);
//         SDL_Delay(3000);
  
 

//         clearTextArea(renderer, 50, 550, 300, 30, 255, 0, 0, 0);
//         printf("2\n");
//         SDL_Delay(3000);

//         // Clear text area
//         renderText(renderer, font, "enemy", 450, 10);
//         // HPバーの描画enemy
//         renderHPBarenemy(renderer, 450, 50, 300, 30, currentHP, maxHP);
//         // HPバーの描画pika
//         renderText(renderer, font, "pika", 50, 450);
//         renderHPBarpika(renderer, 50, 500, 300, 30, currentHP, maxHP);

//         renderText(renderer, font, "pikemon is still fighting.", 50, 550);
//         printf("3\n");
//         SDL_RenderPresent(renderer);
//         SDL_Delay(3000);
 

//         // Clear text area again
//         clearTextArea(renderer, 50, 550, 300, 30, 255, 0, 0, 0);
//         printf("4\n");

//         SDL_Delay(1000); // 60FPSに調整*/
//     }

//     TTF_CloseFont(font);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     TTF_Quit();
//     SDL_Quit();

//     return 0;
// }



// /*


// int main(int argc, char* argv[])
// {

//                 //pika is stronger then ememy
               
//             }
//             //ここまで新しく書いた所24/11/2024//

//             if (enemy_party[j].hp <= 0)//敵のhpが０になったらpartyから外れる
//             {
//                 sleep(second);
//                 printf("%s's hp is 0! %s will be gone.\n", enemy_party[j].name, enemy_party[j].name);
//                 enemy_party[j].active = 0;
//                 enemy_active_number --;
//                 pika_party[pika_party_size] = enemy_party[j];
//                 printf("%s has joined pika_party\n", pika_party[pika_party_size].name);
//                 pika_party[pika_party_size].hp = 150;
//                 pika_party[pika_party_size].active = 1;
//                  pika_active_number ++;

//                 printf("%s ,s hp became %d\n", pika_party[pika_party_size].name, pika_party[pika_party_size].hp);
//                 pika_party_size++;
//                 printf("pika_party\n");
//                 for(int i = 0; i < pika_party_size; i++)
//                 {
//                     printf("name:%s level:%d hp:%d active:%d\n", pika_party[i].name,
//                     pika_party[i].level, pika_party[i].hp, pika_party[i].active);
//                 }

//             }

//             if(pika_party[fight_pokemon].hp <= 0)
//             {
//                 pika_party[fight_pokemon].active = 0;
//                 pika_active_number --;

//             }
             
           

           
//             int save_choice;
//             printf("do you want to save this game and finish(1)? or continue(2)\n");
//             scanf("%d", &save_choice);
//             if(save_choice == 1)
//             {
//                 const char *file_save_enemy = "save_enemy.csv";
//                 export_enemy_CSV(file_save_enemy, enemy_party);
//                 printf("hello\n");

//                 const char *file_save_pika = "save_pika.csv";
//                 export_pika_CSV(file_save_pika, pika_party, pika_party_size);
//                 break;
//             }

//             else if(save_choice == 2)
//             {
//                 if(pika_active_number == 0)
//                 {
//                     printf("pika party have lost!! SAD!!!\n");
//                     break;
//                 }
//                 else if(enemy_active_number == 0)
//                 {
//                     printf("enemy party have lost!! pika party won! yaaay!!!\n");
//                     break;
//                 }
//                 else
//                 {
//                     continue;
//                 }
//             }
            
            
//         }
//         else if(choice == 4)
//         {
//             //printf("choice is %d\n", choice);
//             printf("pika run away\n");
//         }
       
//     }
//     // リソースの解放
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }*/