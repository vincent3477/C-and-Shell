#pragma once

char spin_dreidel(void);

int play_game(int n_players, int coins_per_player, int * n_rounds);  

void set_print_eliminations_true();

void init_seed(long init);
