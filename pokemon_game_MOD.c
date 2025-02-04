#include "pokemon_game_func.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
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

int second = 3;
int pika_party_size = 1;

char buffer[200];
char message_enemy_attack[][200];
char message_pika_attack[5][300];

void renderPokemonImage(SDL_Renderer* renderer, const char* image_path, int x, int y, int width, int height) {
    // Load image
    //printf("%s\n", image_path);
    SDL_Surface *image_surface = IMG_Load(image_path);
    if (!image_surface) {
        fprintf(stderr, "Error loading image %s: %s\n", image_path, IMG_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);

    if (!texture) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        return;
    }

    // Set destination rectangle
    SDL_Rect dest_rect = {x, y, width, height};

    // Render image
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);

    // Clean up
    SDL_DestroyTexture(texture);
}

// HP bar for pika
void renderHPBarpika(SDL_Renderer* renderer, int x, int y, int width, int height, int currentHP, int maxHP) {
    // HP background bar（gray）
    SDL_Rect bgRect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // gray
    SDL_RenderFillRect(renderer, &bgRect);

    // HP bar（green）
    SDL_Rect hpRect = {x, y, (int)((float)currentHP / maxHP * width), height};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &hpRect);
}

// HP bar for enemy
void renderHPBarenemy(SDL_Renderer* renderer, int x, int y, int width, int height, int currentHP, int maxHP) {
    // HP background bar（gray）
    SDL_Rect bgRect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // gray
    SDL_RenderFillRect(renderer, &bgRect);

    // HP bar（green）
    SDL_Rect hpRect = {x, y, (int)((float)currentHP / maxHP * width), height};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &hpRect);
}

// text
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color textColor = {255, 255, 255, 255}; // white
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (!textSurface) {
        fprintf(stderr, "Failed to render text: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set to white
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

int clearTextArea(SDL_Renderer* renderer, int x, int y, int w, int h, int blend, int r, int g, int b) {
    // fill the background with black to delete the the words
    SDL_Rect clearRect;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    clearRect.x = x;
    clearRect.y = y;
    clearRect.w = w;
    clearRect.h = h;

    SDL_SetRenderDrawColor(renderer, r, g, b, blend);
    SDL_RenderFillRect(renderer, &clearRect);
    //SDL_RenderPresent(renderer);

    return 0;
}


int main() 
{
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("battle scene", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 24);
    if (!font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }


    int currentHP = 70;
    int maxHP = 150;

    SDL_Event e;
    int quit = 0;
    int attack_choice_pika = 0;

    // clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int party_size = 0;
    int active_size = 2;

    int choice_data;
    renderText(renderer, font, "do you want to use first data(1) or save data(2)", 50, 550);
    SDL_RenderPresent(renderer);
    printf("do you want to use first data(1) or save data(2)\n");//word1
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
    
    char messages[2][256];

    while (!quit || pika_active_number != 0 || enemy_active_number != 0) 
    {
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_QUIT)
             {
                quit = 1;
            }
        }


         //pick the random ememy pikomon
        int j;
        do
        {
            j = rand() % Pokemon_Max_Level;
        } while (!enemy_party[j].active);
        
        //initialize pika, enemy HP bar
        clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
        clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
        clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
        clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika_attack
        //initialize words from x 400 to 550
        clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
        clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
        clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
        clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);

        // draw HP-bar enemy
        snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
        renderText(renderer, font, buffer, 300, 10);
        renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
        printf("enemy:%s pika:%s\n", enemy_party[j].image, pika_party[fight_pokemon].image);
        //enemy_image
        renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

        //pika_image
        renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
        // draw HP-bar pika
        snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
        renderText(renderer, font, buffer, 50, 300);
        renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);
        

        //delite word1      
        clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);

        snprintf(buffer, sizeof(buffer), "%s has appered! level %d hp %d", enemy_party[j].name, enemy_party[j].level, enemy_party[j].hp);
        renderText(renderer, font, buffer, 50, 500);
        printf("%s has appered! level %d hp %d\n", enemy_party[j].name, enemy_party[j].level, enemy_party[j].hp);
        renderText(renderer, font, "fight(1) or run away(2)", 50, 550);
        printf("fight(1) or run away(2)\n");
        SDL_RenderPresent(renderer);

        int choice;
        scanf("%d", &choice);
        if(choice == 1)
        {
            //change pokemon if pika_party has more then 1 pokemon
            if(pika_party_size > 1)
            {
                int through_first = 0;
                int change_pika_party;
                do
                {
                    printf("hrough_first:%d, pika_party[change_pika_party].hp:%d\n", through_first, pika_party[change_pika_party].hp);
                    if(through_first == 1 && pika_party[change_pika_party].hp == 0)
                    {
                        printf("1");
                        clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                        clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                        clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                        clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
                        snprintf(buffer, sizeof(buffer), "%s's HP is 0. choose another one", pika_party[change_pika_party].name);
                        renderText(renderer, font, buffer, 50, 400);
                        SDL_RenderPresent(renderer);
                        sleep(second);
                    }
                    //initialize pika, enemy HP bar
                    clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                    clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika_attack
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);
                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
                    
                    renderText(renderer, font, "Do you want to change pokemon?", 50, 400);
                    int moveX_pika = 0;
                    int count4_pika = 0;
                    for(int i=0; i < pika_party_size; i++)
                    {
                        snprintf(buffer, sizeof(buffer), "(%d)%s[%d/150]", i, pika_party[i].name, pika_party[i].hp);
                        printf("%d:%s\n", i, pika_party[i].name);
                        if(count4_pika <= 2)
                        {
                            renderText(renderer, font, buffer, 50 + moveX_pika, 450);
                            moveX_pika += 250;
                            count4_pika ++;
                            printf("moveX:%d count4:%d\n", moveX_pika, count4_pika);
                        }
                        else
                        {
                            if(count4_pika == 3)
                            {
                                moveX_pika = 0;
                            }
                            renderText(renderer, font, buffer, 50 + moveX_pika, 500);
                            moveX_pika += 250;
                            count4_pika ++;
                            printf("moveX_under:%d\n", moveX_pika);
                        }
                        
                    }
                    renderText(renderer, font, "press number", 50, 550);
                    printf("press number\n");
                    SDL_RenderPresent(renderer);
                    scanf("%d", &change_pika_party);
                    through_first = 1;
                }while(pika_party[change_pika_party].hp <=0);
                
                fight_pokemon = change_pika_party;
            }
            while(pika_party[fight_pokemon].hp >=0 || enemy_party[j].hp >=0)//until one of them win
            {
                //initialize pika, enemy HP bar
                clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                clearTextArea(renderer, 50, 350, 900, 30, 255, 0, 0, 0);//pika_attack
                //initialize words from x 400 to 550
                clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);

                //if ememy is stronger then pika_party
                if (enemy_party[j].speed > pika_party[fight_pokemon].speed)
                {
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);        
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

                    snprintf(buffer, sizeof(buffer), "%s attacked %s", enemy_party[j].name, pika_party[fight_pokemon].name);
                    renderText(renderer, font, buffer, 50, 400);
                    
                    sleep(second);
                    int temp_enemy_a1_power = enemy_party[j].attack1_power;
                    int temp_enemy_a2_power = enemy_party[j].attack2_power;
                    printf("t_e_a1_p:%d t_e_a2_p:%d\n", temp_enemy_a1_power, temp_enemy_a2_power);

                    type_pokemon_enemy_attack(enemy_party, pika_party, j, fight_pokemon, messages);
                    renderText(renderer, font, messages[0], 50, 450);
                    renderText(renderer, font, messages[1], 50, 500);
                    SDL_RenderPresent(renderer);
                    sleep(second);
                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);

                    
                    int enemy_index = enemy_attack(j, fight_pokemon, message_enemy_attack);
                    printf("enemy_index: %d\n", enemy_index);
                    if(enemy_index == 3)
                    {
                        renderText(renderer, font, message_enemy_attack[0], 50, 400);
                        renderText(renderer, font, message_enemy_attack[1], 50, 450);
                    }
                    else if(enemy_index == 4)
                    {
                        renderText(renderer, font, message_enemy_attack[2], 50, 400);
                    }

                    //initialize pika, enemy HP words
                    clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                    clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                    clearTextArea(renderer, 50, 350, 900, 30, 255, 0, 0, 0);//pika_attack
                    
                    
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);


                    enemy_party[j].attack1_power = temp_enemy_a1_power;
                    enemy_party[j].attack2_power = temp_enemy_a2_power;
                    printf("e_a1_p:%d w_a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);


                    if(pika_party[fight_pokemon].hp <= 0)
                    {
                        snprintf(buffer, sizeof(buffer), "%s's hp is 0. %s lost\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name);
                        printf("%s's hp is 0. %s lost\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name);
                        renderText(renderer, font, buffer, 50, 500);
                        SDL_RenderPresent(renderer);
                        sleep(second);
                        
                        break;
                    }
                    else
                    {
                        snprintf(buffer, sizeof(buffer), "%s's hp is %d\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
                        printf("%s's hp is %d\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
                        renderText(renderer, font, buffer, 50, 500);
                        SDL_RenderPresent(renderer);
                    }
                    sleep(second);

                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    printf("pikahp:%d\n", pika_party[fight_pokemon].hp);
                    snprintf(buffer, sizeof(buffer), "%s's turn. %s attacked %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name, enemy_party[j].name);
                    renderText(renderer, font, buffer, 50, 400);
                    printf("%s's turn. %s attacked %s\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name, enemy_party[j].name);
                    int temp_pika_a1_power = pika_party[fight_pokemon].attack1_power;
                    int temp_pika_a2_power = pika_party[fight_pokemon].attack2_power;
                    printf("t_p_a1_p:%d t_p_a2_p:%d\n", temp_pika_a1_power, temp_pika_a2_power);

                    type_pokemon_pika_attack(enemy_party, pika_party, j, fight_pokemon, messages);
                    /*--------------------------------------------------------------------*/
                    clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                    clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika_attack
                    
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);
                    /*------------------------------------------------------------------*/
                    renderText(renderer, font, messages[0], 50, 450);
                    renderText(renderer, font, messages[1], 50, 500);
                    SDL_RenderPresent(renderer);
                    sleep(second);
                    
                    //initialize pika, enemy HP bar
                    clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                    clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                    clearTextArea(renderer, 50, 350, 900, 30, 255, 0, 0, 0);//pika_attack
                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
                    
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);                  
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

                    snprintf(buffer, sizeof(buffer), "%s's turn\n", pika_party[fight_pokemon].name);
                    printf("%s's turn\n", pika_party[fight_pokemon].name);
                    renderText(renderer, font, buffer, 50, 400);

                    renderText(renderer, font, "which move do you want to use?(1) or (2)", 50, 450);
                    snprintf(buffer, sizeof(buffer), "(1)attack:%s, damege:%d, accurecy:%d",
                    pika_party[fight_pokemon].attack1, pika_party[fight_pokemon].attack1_power, 
                    pika_party[fight_pokemon].attack1_accuracy);
                    renderText(renderer, font, buffer, 50, 500);
                    snprintf(buffer, sizeof(buffer), "(2)attack:%s, damege:%d, accurecy:%d",
                    pika_party[fight_pokemon].attack2, pika_party[fight_pokemon].attack2_power, 
                    pika_party[fight_pokemon].attack2_accuracy);
                    renderText(renderer, font, buffer, 50, 550);
                    printf("which move do you want to use?(1)attack:%s, damege:%d, accurecy:%d or (2)attack:%s, damege:%d, accurecy:%d\n",
                    pika_party[fight_pokemon].attack1, pika_party[fight_pokemon].attack1_power, 
                    pika_party[fight_pokemon].attack1_accuracy, pika_party[fight_pokemon].attack2,
                    pika_party[fight_pokemon].attack2_power, pika_party[fight_pokemon].attack2_accuracy);
                    
                    SDL_RenderPresent(renderer);
                    scanf("%i", &attack_choice_pika);
                    printf("attack_choice_pika: %i\n", attack_choice_pika);


                    int pika_index = pika_attack(fight_pokemon, j, attack_choice_pika, message_pika_attack);
                    
                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);

                    if(pika_index == 3)
                    {
                        renderText(renderer, font, message_pika_attack[2], 50, 400);
                        renderText(renderer, font, message_pika_attack[3], 50, 450);
                    }
                    else if(pika_index == 4)
                    {
                        renderText(renderer, font, message_pika_attack[4], 50, 400);
                    }

                    //initialize pika, enemy HP words
                    clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 300, 500, 30, 255, 0, 0, 0);
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);               
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

                    pika_party[fight_pokemon].attack1_power = temp_pika_a1_power;
                    pika_party[fight_pokemon].attack2_power = temp_pika_a2_power;
                    printf("p_a1_p:%d p_a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);

                    

                    if(enemy_party[j].hp <= 0)
                    {
                        snprintf(buffer, sizeof(buffer), "%s's hp is 0. %s lost\n", enemy_party[j].name, enemy_party[j].name);
                        printf("%s's hp is 0. %s lost\n", enemy_party[j].name, enemy_party[j].name);
                        renderText(renderer, font, buffer, 50, 500);
                        SDL_RenderPresent(renderer);
                        sleep(second);
                        break;
                    }
                    else
                    {
                        snprintf(buffer, sizeof(buffer), "%s's hp is %d\n", enemy_party[j].name, enemy_party[j].hp);
                        printf("%s's hp is %d\n", enemy_party[j].name, enemy_party[j].hp);
                        renderText(renderer, font, buffer, 50, 500);
                        SDL_RenderPresent(renderer);
                    }
                    sleep(second);

                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
                }
                //*******************************************************************************************
                //pika is stronger then ememy
                else if(pika_party[fight_pokemon].speed > enemy_party[j].speed )
                {

                    snprintf(buffer, sizeof(buffer), "%s attacked %s", pika_party[fight_pokemon].name, enemy_party[j].name);
                    renderText(renderer, font, buffer, 50, 400);
                    
                    
                    int temp_pika_a1_power = pika_party[fight_pokemon].attack1_power;
                    int temp_pika_a2_power = pika_party[fight_pokemon].attack2_power;
                    printf("t_p_a1_p:%d t_p_a2_p:%d\n", temp_pika_a1_power, temp_pika_a2_power);

                    type_pokemon_pika_attack(enemy_party, pika_party, j, fight_pokemon, messages);
                    

                    clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                    clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                    clearTextArea(renderer, 50, 350, 900, 30, 255, 0, 0, 0);//pika_attack
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);               
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

                    renderText(renderer, font, messages[0], 50, 450);
                    renderText(renderer, font, messages[1], 50, 500);
                    SDL_RenderPresent(renderer);
                    sleep(second);
 
                    clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                    clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                    clearTextArea(renderer, 50, 350, 900, 30, 255, 0, 0, 0);//pika_attack
                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);               
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

                    snprintf(buffer, sizeof(buffer), "%s's turn\n", pika_party[fight_pokemon].name);
                    printf("%s's turn\n", pika_party[fight_pokemon].name);
                    renderText(renderer, font, buffer, 50, 400);

                    
                    renderText(renderer, font, "which move do you want to use?(1)or(2)", 50, 450);
                    snprintf(buffer, sizeof(buffer), "(1)attack:%s, damege:%d, accurecy:%d",
                    pika_party[fight_pokemon].attack1, pika_party[fight_pokemon].attack1_power, 
                    pika_party[fight_pokemon].attack1_accuracy);
                    renderText(renderer, font, buffer, 50, 500);
                    snprintf(buffer, sizeof(buffer), "(2)attack:%s, damege:%d, accurecy:%d", pika_party[fight_pokemon].attack2,
                    pika_party[fight_pokemon].attack2_power, pika_party[fight_pokemon].attack2_accuracy);
                    renderText(renderer, font, buffer, 50, 550);
                    printf("which move do you want to use?(1)attack:%s, damege:%d, accurecy:%d or (2)attack:%s, damege:%d, accurecy:%d\n",
                    pika_party[fight_pokemon].attack1, pika_party[fight_pokemon].attack1_power, 
                    pika_party[fight_pokemon].attack1_accuracy, pika_party[fight_pokemon].attack2,
                    pika_party[fight_pokemon].attack2_power, pika_party[fight_pokemon].attack2_accuracy);
                    
                    SDL_RenderPresent(renderer);
                    scanf("%i", &attack_choice_pika);
                    printf("attack_choice_pika: %i\n", attack_choice_pika);


                    int pika_index = pika_attack(fight_pokemon, j, attack_choice_pika, message_pika_attack);
                    
                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
  
                    if(pika_index == 3)
                    {
                        renderText(renderer, font, message_pika_attack[2], 50, 400);
                        renderText(renderer, font, message_pika_attack[3], 50, 450);
                    }
                    else if(pika_index == 4)
                    {
                        renderText(renderer, font, message_pika_attack[4], 50, 400);
                    }
  
                    //initialize pika, enemy HP words
                    clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                    clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                    clearTextArea(renderer, 50, 350, 900, 30, 255, 0, 0, 0);//pika_attack
                    
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);               
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

                    pika_party[fight_pokemon].attack1_power = temp_pika_a1_power;
                    pika_party[fight_pokemon].attack2_power = temp_pika_a2_power;
                    printf("p_a1_p:%d p_a2_p:%d\n", pika_party[fight_pokemon].attack1_power, pika_party[fight_pokemon].attack2_power);



                    if(enemy_party[j].hp <= 0)
                    {
                        snprintf(buffer, sizeof(buffer), "%s's hp is 0. %s lost\n", enemy_party[j].name, enemy_party[j].name);
                        printf("%s's hp is 0. %s lost\n", enemy_party[j].name, enemy_party[j].name);
                        renderText(renderer, font, buffer, 50, 500);
                        SDL_RenderPresent(renderer);
                        sleep(second);
                        break;
                    }
                    else
                    {
                        snprintf(buffer, sizeof(buffer), "%s's hp is %d\n", enemy_party[j].name, enemy_party[j].hp);
                        printf("%s's hp is %d\n", enemy_party[j].name, enemy_party[j].hp);
                        renderText(renderer, font, buffer, 50, 500);
                        SDL_RenderPresent(renderer);
                    }
                    
                    sleep(second);

                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
                    
                    snprintf(buffer, sizeof(buffer), "%s's turn. %s attacked %s\n", enemy_party[j].name, enemy_party[j].name, pika_party[fight_pokemon].name);
                    printf("%s's turn. %s attacked %s\n", enemy_party[j].name, enemy_party[j].name, pika_party[fight_pokemon].name);
                    renderText(renderer, font, buffer, 50, 400);
                    sleep(second);
                    int temp_enemy_a1_power = enemy_party[j].attack1_power;
                    int temp_enemy_a2_power = enemy_party[j].attack2_power;
                    printf("t_e_a1_p:%d t_e_a2_p:%d\n", temp_enemy_a1_power, temp_enemy_a2_power);

                    type_pokemon_enemy_attack(enemy_party, pika_party, j, fight_pokemon, messages);
                    /*---------------------------------------------*/
                    //initialize pika, enemy HP words
                    clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                    clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                    clearTextArea(renderer, 50, 350, 900, 30, 255, 0, 0, 0);//pika_attack
                    
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);               
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);
                    /*-------------------------------------------------------*/
                    renderText(renderer, font, messages[0], 50, 450);
                    renderText(renderer, font, messages[1], 50, 500);
                    SDL_RenderPresent(renderer);
                    sleep(second);

                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);

                    int enemy_index = enemy_attack(j, fight_pokemon, message_enemy_attack);
                    printf("enemy_index: %d\n", enemy_index);
                    if(enemy_index == 3)
                    {
                        renderText(renderer, font, message_enemy_attack[0], 50, 400);
                        renderText(renderer, font, message_enemy_attack[1], 50, 450);
                    }
                    else if(enemy_index == 4)
                    {
                        renderText(renderer, font, message_enemy_attack[2], 50, 400);
                    }

                    //initialize pika, enemy HP words
                    clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                    clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                    clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                    clearTextArea(renderer, 50, 350, 900, 30, 255, 0, 0, 0);//pika_attack
                    
                    // draw HP-bar enemy
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                    renderText(renderer, font, buffer, 300, 10);
                    renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                    //enemy_image
                    renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                    //pika_image
                    renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                    // draw HP-bar pika
                    snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                    renderText(renderer, font, buffer, 50, 300);               
                    renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);

                    enemy_party[j].attack1_power = temp_enemy_a1_power;
                    enemy_party[j].attack2_power = temp_enemy_a2_power;
                    printf("e_a1_p:%d w_a2_p:%d\n", enemy_party[j].attack1_power, enemy_party[j].attack2_power);


                    if(pika_party[fight_pokemon].hp <= 0)
                    {
                        snprintf(buffer, sizeof(buffer), "%s's hp is 0. %s lost\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name);
                        printf("%s's hp is 0. %s lost\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].name);
                        renderText(renderer, font, buffer, 50, 500);
                        SDL_RenderPresent(renderer);
                        sleep(second);
                        break;
                    }
                    else
                    {
                        snprintf(buffer, sizeof(buffer), "%s's hp is %d\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
                        printf("%s's hp is %d\n", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp);
                        renderText(renderer, font, buffer, 50, 500);
                        SDL_RenderPresent(renderer);
                    }
                    sleep(second);

                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                }
            }

            if (enemy_party[j].hp <= 0)//leave enemt_party if enemy pikemon's HP is 0
            {
                //initialize pika, enemy HP words
                clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
                clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
                clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
                clearTextArea(renderer, 50, 350, 900, 30, 255, 0, 0, 0);//pika_attack
                
                // draw HP-bar enemy
                snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
                renderText(renderer, font, buffer, 300, 10);
                renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
                //enemy_image
                renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

                //pika_image
                renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
                // draw HP-bar pika
                snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
                renderText(renderer, font, buffer, 50, 300);               
                renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);
                //initialize words from x 400 to 550
                clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
                sleep(second);
                snprintf(buffer, sizeof(buffer), "%s's hp is 0! %s will be gone.\n", enemy_party[j].name, enemy_party[j].name);
                renderText(renderer, font, buffer, 50, 400);
                printf("%s's hp is 0! %s will be gone.\n", enemy_party[j].name, enemy_party[j].name);
                enemy_party[j].active = 0;
                enemy_active_number --;
                pika_party[pika_party_size] = enemy_party[j];
                snprintf(buffer, sizeof(buffer), "%s has joined pika_party\n", pika_party[pika_party_size].name);
                renderText(renderer, font, buffer, 50, 450);
                printf("%s has joined pika_party\n", pika_party[pika_party_size].name);
                pika_party[pika_party_size].hp = 150;
                pika_party[pika_party_size].active = 1;
                pika_active_number ++;
                
                snprintf(buffer, sizeof(buffer), "%s ,s hp became %d\n", pika_party[pika_party_size].name, pika_party[pika_party_size].hp);
                renderText(renderer, font, buffer, 50, 500);
                printf("%s ,s hp became %d\n", pika_party[pika_party_size].name, pika_party[pika_party_size].hp);
                pika_party_size++;
                SDL_RenderPresent(renderer);
                //initialize words from x 400 to 550
                clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                sleep(second);

                renderText(renderer, font, "pika_party", 50, 400);
                printf("pika_party\n");
                int moveX = 0;
                int count4 = 0;
                for(int i = 0; i < pika_party_size; i++)
                {
                    printf("name:%s level:%d hp:%d active:%d\n", pika_party[i].name,
                    pika_party[i].level, pika_party[i].hp, pika_party[i].active);
                    snprintf(buffer, sizeof(buffer), "%s", pika_party[i].name);
                    if(count4 <= 3)
                    {
                        renderText(renderer, font, buffer, 50 + moveX, 450);
                        moveX += 150;
                        count4 ++;
                        printf("moveX:%d count4:%d\n", moveX, count4);
                    }
                    else
                    {
                        if(count4 == 4)
                        {
                            moveX = 0;
                        }
                        renderText(renderer, font, buffer, 50 + moveX, 500);
                        moveX += 150;
                        count4 ++;
                        printf("moveX_under:%d\n", moveX);
                    }
                    
                    
                }
                SDL_RenderPresent(renderer);
                sleep(second);
                

            }

            if(pika_party[fight_pokemon].hp <= 0)
            {
                pika_party[fight_pokemon].active = 0;
                pika_active_number --;

            }
            //initialize pika, enemy HP words
            clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);//enemy
            clearTextArea(renderer, 100, 50, 900, 30, 255, 0, 0, 0);//enemy_attack
            clearTextArea(renderer, 50, 300, 900, 30, 255, 0, 0, 0);//pika
            clearTextArea(renderer, 50, 350, 900, 30, 255, 0, 0, 0);//pika_attack
            
            // draw HP-bar enemy
            snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
            renderText(renderer, font, buffer, 300, 10);
            renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
            //enemy_image
            renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

            //pika_image
            renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);
            // draw HP-bar pika
            snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
            renderText(renderer, font, buffer, 50, 300);                
            renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);
            //initialize words from x 400 to 550
            clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
            clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
            clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
            int save_choice;
            renderText(renderer, font, "do you want to save this game and finish(1)? or continue(2)\n", 50, 400);
            printf("do you want to save this game and finish(1)? or continue(2)\n");
            SDL_RenderPresent(renderer);
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
                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
                    renderText(renderer, font, "pika party have lost!! SAD!!!", 50, 450);
                    printf("pika party have lost!! SAD!!!\n");
                    SDL_RenderPresent(renderer);
                    sleep(second);
                    break;
                }
                else if(enemy_active_number == 0)
                {
                    //initialize words from x 400 to 550
                    clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
                    clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
                    renderText(renderer, font, "enemy party have lost!! pika party won! yaaay!!!", 50, 450);
                    printf("enemy party have lost!! pika party won! yaaay!!!\n");
                    SDL_RenderPresent(renderer);
                    sleep(second);
                    break;
                }
                else
                {
                    continue;
                }
            }
            
            
        }
        else if(choice == 2)
        {
            //initialize pika, enemy HP words
            clearTextArea(renderer, 250, 10, 900, 30, 255, 0, 0, 0);
            clearTextArea(renderer, 50, 300, 500, 30, 255, 0, 0, 0);
            // draw HP-bar enemy
            snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", enemy_party[j].name, enemy_party[j].hp, enemy_party[j].type, enemy_party[j].speed);
            renderText(renderer, font, buffer, 300, 10);
            renderHPBarenemy(renderer, 450, 50, 300, 30, enemy_party[j].hp, maxHP);
            //enemy_image
            renderPokemonImage(renderer, enemy_party[j].image, 600, 100, 150, 150);

            //pika_image
            renderPokemonImage(renderer, pika_party[fight_pokemon].image, 50, 150, 150, 150);    
            // draw HP-bar pika
            snprintf(buffer, sizeof(buffer), "%s  :%d/150  type:%s  speed:%d", pika_party[fight_pokemon].name, pika_party[fight_pokemon].hp, pika_party[fight_pokemon].type, pika_party[fight_pokemon].speed);
            renderText(renderer, font, buffer, 50, 300);               
            renderHPBarpika(renderer, 50, 350, 300, 30, pika_party[fight_pokemon].hp, maxHP);
            //initialize words from x 400 to 550
            clearTextArea(renderer, 50, 400, 900, 30, 255, 0, 0, 0);
            clearTextArea(renderer, 50, 450, 900, 30, 255, 0, 0, 0);
            clearTextArea(renderer, 50, 500, 900, 30, 255, 0, 0, 0);
            clearTextArea(renderer, 50, 550, 900, 30, 255, 0, 0, 0);
            snprintf(buffer, sizeof(buffer), "%s run away", pika_party[fight_pokemon].name);
            renderText(renderer, font, buffer, 50, 550);
            SDL_RenderPresent(renderer);
            sleep(second);
            printf("pika party run away\n");
        }
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}