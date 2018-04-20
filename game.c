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
 * Prints game information and requests user input.
 *
 * @param
 *  - board: The board object. Contains Token structs.
 *  - player1: The Player object for player 1.
 *  - player2: The Player object for player 2.
 */
void play(Token board[8][8], Player *player1, Player *player2) {
	bool turn = true;
	int count = 0;
	while (count < 2) {
		turn = !turn;
		Player *currentPlayer = turn ? player2 : player1;
		Player *otherPlayer = !turn ? player2 : player1;

		bool broadResult[8][8];
		broadCalculateMoves(broadResult, board, turn);

		//printBoard(board, broadResult, player1, player2);

		bool result[8][8];
		int moves = narrowCalculateMoves(result, broadResult, board, turn);

		printBoard(board, result, player1, player2);

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

		if (count == 2) {
			printf("Game Over!\n");
			if (player1->score > player2->score) {
				printf("Player %s Wins!", player1->name);
			} else {
				printf("Player %s Wins!", player2->name);
			}
			break;
		}
		printf("%s's turn.\n", currentPlayer->name);
		printf("Tokens remaining: %d\n", 32 - currentPlayer->tokensPlaced);

		//NO MOVE POSSIBLE
		int move[2];
		getMove(move, *currentPlayer, result);
		playMove(move, board, currentPlayer, otherPlayer, turn);
	}
	saveToFile(player1, player2);
}

void saveToFile(Player *player1, Player *player2) {
	FILE *fp;
	printf("Game Over!\n");
	
	if ((fp = fopen("scores.txt", "a"))==NULL) {
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
	while (choice == -1) {
		char input[20];
		while(!requestInput(20, input)) {
			printf("Invalid input!1\n> ");
		}
		if (input[1] == '\0') {
			choice = input[0] - 48;
		} else if (input[2] == '\0') {
			choice = (input[0] - 48) * 10 + input[1] - 48;
		} else {
			printf("Invalid input.2\n> ");
			continue;
		}
		if (!(choice > 0 && choice <= count)) {
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
				if (count == choice) {
					move[0] = i;
					move[1] = j;
					return;
				}
			}
		}
	}
}

void broadCalculateMoves(bool result[8][8], Token board[8][8], bool turn) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].type != 10) {
				result[i][j] = false;
				continue;
			}
			bool found = false;
			for (int offsetX = -1; offsetX < 2; offsetX++) {
				for (int offsetY = -1; offsetY < 2; offsetY++) {
					if (offsetX == 0 && offsetX == offsetY)//If we're checking the original square
						continue;
					if (onBoard(i + offsetX, j + offsetY)) {
						if (board[i + offsetX][j + offsetY].type != turn && board[i + offsetX][j + offsetY].type != 10) {//If we're beside an opponent token.
							found = true;
							break;
						}
					}
				}
			}
			result[i][j] = found;
		}
	}
}
int directions[8][2] = {{1,0},{-1,0},{0,-1},{0,1},{1,-1},{1,1},{-1,1}, {-1,-1}};

int narrowCalculateMoves(bool result[8][8], bool broadResult[8][8],  Token board[8][8], bool turn) {
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
				if (board[x][y].type != turn && board[x][y].type != 10) {
					seenEnemyToken = true;
				} else if (board[x][y].type != 10) {
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

bool onBoard(int x, int y) {
	return x <= 7 && x >= 0 && y <= 7 && y >= 0;
}
