#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "game.h"
#include "input.h"

/**
 * Prints the current state of the board.
 *
 * @param
 *  - board: The board object. Contains Token structs.
 *  - player1: The Player object for player 1.
 *  - player2: The Player object for player 2.
 */
void printBoard(Token board[8][8], bool result[8][8], Player *player1, Player *player2) {
	printf("  1 2 3 4 5 6 7 8\n");
	for (int j = 0; j < 8; j++) {
		printf("%d ", j + 1);
		for (int i = 0; i < 8; i++) {
			if (board[i][j].type == 0) {
				printf("%c ", player1->token);
			} else if (board[i][j].type == 1) {
				printf("%c ", player2->token);
			} else {
				if (result[i][j]){
					printf("- ");
				} else {
					printf("  ");
				}
			}
		}
		printf("\n");
 	}
}

/**
 * Zero's memory, sets defaults, requests user properties such as name and token.
 *
 * @param
 *  - board: The board object. Contains Token structs.
 *  - player1: The Player object for player 1.
 *  - player2: The Player object for player 2.
 */
void setup(Token board[8][8], Player *player1, Player *player2) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			//Type 10 value represent empty space.
			board[i][j].type = 10;
		}
 	}

	board[3][3].type = 0;
	board[4][4].type = 0;
	board[4][3].type = 1;
	board[3][4].type = 1;

	requestPlayer(player1, 1);
	requestPlayer(player2, 2);
	
}


/**
 * Request player name and token from user
 *
 * @param
 *  - player: The Player object.
 *  - number: The Player number. 
 */

void requestPlayer(Player *player, int number) {

	char input[20];

	
	printf("Enter Player %d's name: ", number);
	while(!requestInput(20, input)) {
		printf("Invalid input!\n");
		printf("Enter Player %d's name: ", number);
	}
	strcpy(player->name, input);

	printf("Enter Player %d's token: ", number);
	while(!requestInput(20, input) || input[1] != '\0' || input[0] == '-' || (input[0] >= '0' && input[0] <= '9')) {
		printf("Invalid input!\nPlease don't enter '-' and numbers between 0 and 9\n");
		printf("Enter Player %d's token: ", number);
	}
	player->token = input[0];
	player->colour = true;
	player->tokensPlaced = 2;
	player->score = 2;

}
/**
 * Runs the game, follows game rules.
 *
 * @param
 *  - board: The board object. Contains Token structs.
 *  - player1: The Player object for player 1.
 *  - player2: The Player object for player 2.
 */
void play(Token board[8][8], Player *player1, Player *player2) {
	bool turn = true;

	//count: To keep track of the number of no move turns, which when it equals 2, the game will end.
	int count = 0;
	while (count < 2) {
		//Changes who turn it is on each loop.
		turn = !turn;
		Player *currentPlayer = turn ? player2 : player1;
		Player *otherPlayer = !turn ? player2 : player1;

		bool broadResult[8][8];
		broadCalculateMoves(broadResult, board, turn);

		bool result[8][8];
		//moves records the amount of possible moves the player can take.
		int moves = narrowCalculateMoves(result, broadResult, board, turn);

		printBoard(board, result, player1, player2);

		// If there was no possible moves, count will be increased, and the turn will pass.
		if (moves == 0) {
			printf("No possible move for %s!\n", currentPlayer->name);
			count += 1;
			if (count == 2) {
				break;
			}
			continue;
		}
		count = 0;

		printf("Score:\t%20s%3d\n\t%20s%3d\n", player1->name, player1->score, player2->name, player2->score);
		printf("%s's turn.\n", currentPlayer->name);
		printf("Tokens remaining: %d\n", 32 - currentPlayer->tokensPlaced);

		int move[2];
		//Move is returned by parameter from getMove(), and containts the choosen move. It is then passed into playMove().
		getMove(move, *currentPlayer, result);
		playMove(move, board, currentPlayer, otherPlayer, turn);
	}
	saveToFile(player1, player2);
}

/**
 * Saves the game result to a file.
 *
 * @param
 *  - player1: The Player object for player 1.
 *  - player2: The Player object for player 2.
 */
void saveToFile(Player *player1, Player *player2) {
	FILE *fp;
	printf("Game Over!\n");
	if ((fp = fopen("scores.txt", "a")) == NULL) {
		puts("File could not be opened");
	} else {
		printf("Player1 %s, points: %d\nPlayer2 %s, points: %d\n", player1->name, player1->score, player2->name, player2->score);
		fprintf(fp, "Player1 %s, points: %d\nPlayer2 %s, points: %d\n", player1->name, player1->score, player2->name, player2->score);

		if (player1->score == player2->score) {
			printf("The game is a tie!\n!");
			fprintf(fp, "The game is a tie!\n!");
		} else if (player1->score > player2->score) {
			printf("The winner is %s!\n", player1->name);
			fprintf(fp, "The winner is %s!\n", player1->name);
		} else {
			printf("The winner is %s!\n", player2->name);
			fprintf(fp, "The winner is %s!\n", player2->name);
		}
		fclose(fp);
	}
}

/**
 * Asks the user to choose a move. 
 *
 * @param
 *  - move: The resulting move, returned by parameter.
 *  - currentPlayer: The Player object for the current player.
 *  - result: An array of bools, if [i][j] is true, it is a valid move. Should be the result from narrowCalculateMoves.
 */
void getMove(int move[2], Player currentPlayer, bool result[8][8]) {
	printf("%s, choose your move: \n", currentPlayer.name);
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (result[i][j] == true) {
				count++;
				printf("%d. (%d, %d)\t", count, i + 1, j + 1);
			}
		}
	}
	printf("\n> ");
	int choice = -1;
	while (choice == -1) {//Loops until we receive valid input.
		char input[20];
		while(!requestInput(20, input)) {
			printf("Invalid input!1\n> ");
		}
		if (input[1] == '\0') {//If the input was one character long.
			choice = input[0] - 48;//ASSUME that the user input a valid number.
		} else if (input[2] == '\0') {//If the input was two characters long
			choice = (input[0] - 48) * 10 + input[1] - 48;//ASSUME the user put in a valid number, 
		} else {
			printf("Invalid input.2\n> ");
			continue;
		}
		if (!(choice > 0 && choice <= count)) {//Now we check for valid input.
			printf("Invalid input.3\n> ");
			choice = -1;
			continue;
		}
	}
	count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (result[i][j] == true) {
				count++;
				if (count == choice) {//Finds the move pertaining to the users choice and returns it.
					move[0] = i;
					move[1] = j;
					return;
				}
			}
		}
	}
}

/**
 * Broadly calculates valid moves. Checking if there is an adjacent enemy tile.
 *
 * @param
 *  - result: The result, an array of bools. If [i][j] is true, it is a broadly valid move.
 *  - board: The current board state.
 *  - turn: The current turn.
 */
void broadCalculateMoves(bool result[8][8], Token board[8][8], bool turn) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {//Loops through every position on the board.
			if (board[i][j].type != 10) {//If the space isn't blank, we can't possibly move there.
				result[i][j] = false;
				continue;
			}
			bool found = false;
			for (int offsetX = -1; offsetX < 2; offsetX++) {
				for (int offsetY = -1; offsetY < 2; offsetY++) {//Loop through the positions directly around the center (i, j)
					if (offsetX == 0 && offsetX == offsetY)//If we're checking the original square
						continue;
					if (onBoard(i + offsetX, j + offsetY)) {
						if (board[i + offsetX][j + offsetY].type != turn && board[i + offsetX][j + offsetY].type != 10) {//If we're beside an opponent token.
							found = true;
							break;
						}
					}
				}
				if (found) {//No point continuing if we've already found an enemy token.
					break;
				}
			}
			result[i][j] = found;
		}
	}
}

//An array representing all directions that should be checked by the game when calculating moves.
int directions[8][2] = {{1,0},{-1,0},{0,-1},{0,1},{1,-1},{1,1},{-1,1}, {-1,-1}};

/**
 *Identifies the possible moves for the player.
 *
 * @param
 * 	- results: Holds the values for possible moves for the player.
 *  - broadResults: Contains the results of a broad check for possible moves. 
 *  - board: The board object. Contains Token structs.
 * 	- turn: For identifying which player is the current player. 
 */
int narrowCalculateMoves(bool result[8][8], bool broadResult[8][8], Token board[8][8], bool turn) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			result[i][j] = false;
			if (broadResult[i][j] == false) {//If the tile wasn't approved by the broad phase.
				continue;
			}
			for (int direction = 0; direction < 8; direction++) {
				int dx = directions[direction][0];
				int dy = directions[direction][1];
				int x = i;
				int y = j;
				bool seenEnemyToken = false;
				for (int k = 0; k < 7; k++) {//7 is the most amount of "steps" we can take.
					x += dx;
					y += dy;
					if (onBoard(x, y)){
						if (board[x][y].type != turn && board[x][y].type != 10) {//Enemy token
							seenEnemyToken = true;
						} else if (board[x][y].type != 10) {//Our token
							if (seenEnemyToken) {
								result[i][j] = true;
								count++;
							}
							break;
						} else {//Blank token
							break;
						}
					} else {
						break;
					}
				}
			}
		}
	}
	return count;
}

/**
 * Places the players input move, and changes the board depending on the game rule.
 *
 * @param
 * 	- move: The players move.
 *  - board: The board object. Contains Token structs.
 *  - currentPlayer: The Player object for the current player.
 *  - otherPlayer: The Player object for the opposing player.
 * 	- turn: For identifying which player is the current player. 
 */
void playMove(int move[2], Token board[8][8], Player *currentPlayer, Player *otherPlayer, bool turn) {
	board[move[0]][move[1]].type = turn;
	currentPlayer->score = currentPlayer->score + 1;
	for (int direction = 0; direction < 8; direction++) {
		int dx, dy;
		int x, y;
		x = move[0];
		y = move[1];
		dx = directions[direction][0];
		dy = directions[direction][1];
		bool seenEnemyToken = false;
		for (int k = 0; k < 7; k++){//7 is the most amount of "steps" we can take.
			x += dx;
			y += dy;
			if (onBoard(x, y)) {
				//type 10 represents empty token.
				if (board[x][y].type != turn && board[x][y].type != 10) {
					seenEnemyToken = true;
				} else if (board[x][y].type != 10) {
					//Changes opposing player's tokens to the current player's token
					if (seenEnemyToken) {
						for (; k > 0; k--) {
							x -= dx;
							y -= dy;
							board[x][y].type = turn;
							currentPlayer->score = currentPlayer->score + 1;
							otherPlayer->score = otherPlayer->score - 1;
						}
					}
					break;
				} else {
					break;
				}
			} else {
				break;
			}
		}
	}
}

/**
 * Check to see if the currnet location is on the board.
 *
 * @param
 *  - x: First parameter value for the board.
 *  - y: Second parameter value for the board.
 */
]bool onBoard(int x, int y) {
	return x <= 7 && x >= 0 && y <= 7 && y >= 0; //returns true if the current location is on the board.
}
