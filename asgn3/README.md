How to run dreidel.c and play-dreidel.c:

1. Make sure that you are in the correct directory /cse13s/asgn3

2. type "make clean" to clean up other derived files

3. type "make" to make the executables

4. to run the program,

./play-dreidel -c (number of coins from 1-20) -v -s (seed number) -p (number of players from 2-8)

Note: all of these commands are OPTIONAL. -v is an option to print out all eliminations before the end of the game. If no arguments are set ./play-dreidel will run the game with its default values being: players = 4, coins = 3, and seed = 613 

5. The program will print the winner along with the number of players, number of coins, how many rounds it took, and seed number.

For example David 5 6 272 613 is interpreted as David won a 5 player game, where each player started with 6 coins. The game lasted for 272 rounds. The seed number was 613. 

All files included in asgn repo:

1. DESIGN.pdf - This pdf includes how the code is strictured with the use of pseudocode. It also incorporates the purpose of each of the classes, functions, loops, variables, and all other statements

2. dreidel.c - This file includes all the game logic and rules

3. play-dreidel.c -This file allows the client to simulate a game of dreidel, calling functions in the dreidel.c class. In addition, the client is allowed to parse arguments to their preferences. This is where the main() function is contained.

4. dreidel.h - A header file that specifies all the functions that are used across all .c files.

5. Makefile - this will build the exectables and as well removed all previous derived files

6. mtrand.h - A header file that specifies all the mersenne twister related functions to use across different .c files.

7. mtrand.c - Contains the code to generate a repeatable sequence of numbers, based on the seed

8. README.md - This file. Explains how to run the code and what files are included in the /asgn3 repo.

9. WRITEUP.pdf - A file that that contains the analysis of the game including any possible errors produced.
