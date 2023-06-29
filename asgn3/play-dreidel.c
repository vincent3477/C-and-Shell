#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "mtrand.h"
#define OPTIONS "p:s:c:v"
#include "dreidel.h"
int main(int argc, char **argv){
	int opt =0;
	int num_players = 4;
	int num_coins = 3;
	int n_rounds;
	char * player_names[] = {"Aharon", "Batsheva", "Chanah", "David", "Ephraim", "Faige", "Gamaliel", "Hannah"};

	long seed = 613;
	while((opt = getopt(argc, argv, OPTIONS))!=-1){
		switch(opt){
		case 'p':
			num_players = atoi(optarg);
			if ((num_players < 2) || (num_players > 8)){
				return 1;
			}
			break;
		case 'c':
			num_coins = atoi(optarg);
			if ((num_coins < 1) || (num_coins > 20)){
				return 1;
			}	
			break;
		case 's':
			seed = strtoul(optarg, NULL, 10);
 			if ((seed < 0)||(seed > 9999999999)){
				return 1;
			}
			break;	
		case 'v':
			set_print_eliminations_true();	

		default:
			return 1;
		}   
	}
	mtrand_seed (seed);	
	int player_won = play_game(num_players, num_coins,&n_rounds);
	printf("%s %d %d %d %ld\n", player_names[player_won], num_players, num_coins, n_rounds, seed);
	return 0; 
} 

