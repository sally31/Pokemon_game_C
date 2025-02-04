#explain the pokemon game  
##how to play  
This is a pokemon game made in C language and you can play like a real pokemon game but it's only a battle scene.  
There is no walking around the city to explore or talking to someone or catching the wild pokemon by any chance.  
First, you need to choose the file to play which has new data for new player or saved data if you saved before.  
If you use the new data, you have a only pikachu to fight against enemy and enemy team has 6 pokemon which are smeargle, yamper, dachsbun, greavard, bidoof and fuecoco.  
one of them will appear randomly but you can choose to fight or run away.  
If you choose to run away, the other ramdom enemy will appear.  
If you decided to fight, the faster move pokemon will attack first also all of the pokemon has 2 different attack and different attack power and accuracy.  
Before attack, the type also will be calucurated.  
they have fire, ghost, normal, electric and fairy type.  
  
if you are fire type, attack power will be 0 to ghost type but power will be double to normal type.  
If you are ghost type, attack power will be bouble to ghost and electric.  
If you are normal type, attack power will be half to ghost but power will be double to fairy.  
If you are electric type, attack power will be half to electric and fire but power will be double to fairy.  
If you are fairy type, attack power will be half to electric but power will be double to ghost and fire.  
  
Make sure to remember the type.  
If the enemy is faster then pikachu they will be chosen one of the attack ramdomly but before the attack, accuracy will be calucurated so it might be missed then next turn will be your turn.  
In your turn you can choose which attack you want to use but be carefull, stronger attack power have less accuracy even if you always want to use stonger one, it might miss and your turn will end.  
The battle will be continued until one of them will win so if enemy won, you have only pikachu so far so which mean you lost and game finished so you need to be carefull to check you can win or not before the game start.  
If you won the game you will get the pokemon from enemy team that you just beated in the battle.  
Every time after finish the battle the game will ask you to keep continue to play or save the data and finish the game.  
If you choose to keep continue, from the next game you can choose which pokemon in your team you want to use for the next fight and start fighting as before until all pokemon on one team are defeated them the game will be completely finished.  

##explain all of the files.  
there are enemy_party.csv and pika_party.csv files.  
they have infomations for pokemon name, level, hp, type, attack1, attack1_power, attack1_accuracy, attack2, attack2_power, attack2_accuracy, speed and active.  
everyone have level 50 and hp 150 also everyone have 2 attacks and each one have different attack power and accuracy.  
each pokemon has different speed.  
active is on nutil the pokemon lose. if the pokemon lost active will be off so the pokemon won't be chosen for the fight.  
Why I made CSV files and import them instead of write it in the code and it's easer, because if you want to edit the infomation you have to re-write it in the code which may cause you accidently delete your code or bugs that's why I made CSV files.  

###there are enemy_import_export.c and pika_import_export.c files.  
this is for import the csv files before you play game and export the files if you want to save data also import the save data as well if you want to use save data.  
I made 2 files for each one because it's quite complicated and long code so it might have mixed also defficult to read which may cause some bugs.  

###there is a type_check.c file.  
this is for checking the attacker's pokemon's type and change the attack power if needed.  
It will be called in the main file just before they attack.  
  
there is a main file called pokemon_game_MOD.c file.  
there is written fighting scene and call all of the functions.  
  
there is pokemon_game_func.h file.  
this is a header file and connect all of the functions.  
But when you compile them you need compile below.  
## put compile later
