#include "dreidel.h"
#include <stdio.h>
#include "mtrand.h"

char * player_names[] = {"Aharon", "Batsheva", "Chanah", "David", "Ephraim", "Faige", "Gamaliel", "Hannah"};

int print_eliminations = 0;

void set_print_eliminations_true(){
	print_eliminations = 1;
}



char spin_dreidel(){
	long rand_num_generated = mtrand_rand64() % 4;
	if (rand_num_generated == 0){
		return 'G';
		}
	else if (rand_num_generated == 1){
		return 'H'; 
		}
	else if (rand_num_generated == 2){
		return 'N';
		}
	else 	{
		return 'S';
		}
}


int play_game(int n_players, int coins_per_player, int * n_rounds){
	*n_rounds = 1;
	int pot = 0;
	int player_coins[8] = {coins_per_player, coins_per_player, coins_per_player, coins_per_player, coins_per_player, coins_per_player, coins_per_player, coins_per_player};	


	int participating_players = n_players;
	while (1){
		for(int i = 0; i < n_players; i++){
			if (player_coins[i] != -1){
				char dreidel_result = spin_dreidel();
				if (dreidel_result == 'G'){
					player_coins[i] += pot;
					pot = 0;
					}	
				else if (dreidel_result == 'H'){
					player_coins[i] += (pot/2);
					pot -= (pot/2);			
					}
				else if (dreidel_result == 'S'){
				
					if (player_coins[i] == 0){
						participating_players -= 1;
						player_coins[i] = -1;
						if (print_eliminations){
							printf("%s: eliminated in round %d of a %d player game.\n", player_names[i], *n_rounds, n_players);           
						}	
					}
					else{
					player_coins[i] -= 1;
					pot += 1;
					}
					
				}
			}


		}
							
		if (participating_players == 1){
			for(int j = 0; j < n_players; j++){
				if (player_coins[j] != -1){
					return j; 
					}
				}
				
		
			}
		*n_rounds += 1;
		}
	}		
	
