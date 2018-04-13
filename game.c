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
	for (int i = 0; i < 8; i++) {
		printf("%d ", i + 1);
		for (int j = 0; j < 8; j++) {
			if (board[i][j].type == 0) {
				printf("%c ", player1->token);
			} else if (board[i][j].type == 1) {
				printf("%c ", player2->token);
			} else {
			    if (result[i][j]){
                    printf("P ");
                } else {
                    printf("- ");
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

	char input[20];

	printf("Enter Player 1's name: ");
	while(!requestInput(20, input)) {
		printf("Invalid input!\n");
		printf("Enter Player 1's name: ");
	}
	strcpy(player1->name, input);

	printf("Enter Player 1's token: ");
	while(!requestInput(20, input) || input[1] != '\0') {
		printf("Invalid input!\n");
		printf("Enter Player 1's token: ");
	}
	player1->token = '0';
	player1->colour = true;
	player1->tokensPlaced = 2;
	player1->score = 2;

	printf("Enter Player 2's name: ");
	while(!requestInput(20, input)) {
		printf("Invalid input!\n");
		printf("Enter Player 2's name: ");
	}
	strcpy(player2->name, input);

	printf("Enter Player 2's token: ");
	while(!requestInput(20, input) || input[1] != '\0') {
		printf("Invalid input!\n");
		printf("Enter Player 2's token: ");
	}
	player2->token = '1';
	player2->colour = false;
	player2->tokensPlaced = 2;
	player2->score = 2;
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
	while (true) {
		turn = !turn;
		Player currentPlayer = turn ? *player2 : *player1;

		bool broadResult[8][8];
		broadCalculateMoves(broadResult, board, turn);

		bool result[8][8];
		narrowCalculateMoves(result, broadResult, board, turn);

		printBoard(board, result, player1, player2);
		printf("%s's turn.\n", currentPlayer.name);
		printf("Tokens remaining: %d\n", 32 - currentPlayer.tokensPlaced);

		//NO MOVE POSSIBLE
		int move[2];
		getMove(move, currentPlayer, result);
		
	}
}

void getMove(int move[2], Player currentPlayer, bool result[8][8]) {
	printf("%s, choose your move: \n", currentPlayer.name);
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (result[i][j] == true) {
				printf("%d. (%d, %d)\t", ++count, i, j);
			}
		}
	}
	printf("\n> ");
	int choice = -1;
	while (choice == -1) {
		char input[20];
		while(!requestInput(20, input)) {
			printf("Invalid input!\n> ");
		}
		if (input[1] == '\0') {
			choice = input[0] - 48;
		} else if (input[2] = '\0') {
			choice = (input[0] - 48) * 10 + input[1] - 48;
		} else {
			printf("Invalid input.\n> ");
			continue;
		}
		if (!(choice > 0 && choice <= count)) {
			printf("Invalid input.\n> ");
			choice = -1;
			continue;				
		}
	}
	count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (result[i][j] == true) {
				if (++count == choice) {
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
			bool found = false;
			for (int offsetX = -1; offsetX < 2; offsetX++) {
				for (int offsetY = -1; offsetY < 2; offsetY++) {
				    if (offsetX == 0 && offsetX == offsetY)
                        continue;
					if (i + offsetX >= 0 && i + offsetX < 8 && j + offsetY >= 0 && j + offsetY < 8) {//On board
                        if (board[i][j].type == 10 && board[i + offsetX][j + offsetY].type != turn && board[i + offsetX][j + offsetY].type != 10) {
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
int moves[8][2] = {{1,0},{-1,0},{0,-1},{0,1},{1,-1},{1,1},{-1,1}, {-1,-1}};

void narrowCalculateMoves(bool result[8][8], bool boardResult[8][8],  Token board[8][8], bool turn) {
    printf("Turn: %d", turn);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
            result[i][j] = false;
		    if (boardResult[i][j] == false) {
                continue;
		    }
			for (int move = 0; move < 8; move++){
                int dx, dy;
                dx = moves[move][0];
                dy = moves[move][1];
                int x, y;
                x = i;
                y = j;
                bool seenEnemyToken = false;
                for (int k = 0; k < 7; k++){
                    x += dx;
                    y += dy;
                    if ((x <= 7 && x >= 0)&&(y <= 7 && y >= 0)){
                        if (board[x][y].type != turn) {
                            seenEnemyToken = true;
                        } else if (board[x][y].type != 10){
                            if (seenEnemyToken) {
                                result[i][j] = true;
                            }
                        } else {
                            break;
                        }
                    } else {
                        break;
                    }
                }
			}
		}
	}
}
