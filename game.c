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
void printBoard(Token board[8][8], Player *player1, Player *player2) {
	printf("  1 2 3 4 5 6 7 8\n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", i + 1);
		for (int j = 0; j < 8; j++) {
			if (board[i][j].type == 0) {
				printf("%c ", player1->token);
			} else if (board[i][j].type == 1) {
				printf("%c ", player2->token);
			} else {
				printf("- ");
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
	player1->token = input[0];
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
	player2->token = input[0];
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
	bool turn = false;
	while (true) {
		turn = !turn;
		Player currentPlayer = turn ? *player1 : *player2;
		printBoard(board, player1, player2);
		printf("%s's turn.\n", currentPlayer.name);
		printf("Tokens remaining: %d\n", 32 - currentPlayer.tokensPlaced);

		bool result[8][8];
		broadCalculateMoves(result, board, turn);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				printf("%d ", result[i][j]);
			}
			printf("\n");
		}		
		char input[20];
		printf("Enter input to continue.");
		requestInput(20, input);
	}
}

void broadCalculateMoves(bool result[8][8], Token board[8][8], bool turn) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			bool found = false;
			for (int offsetX = -1; offsetX < 2; offsetX++) {
				for (int offsetY = -1; offsetY < 2; offsetY++) {
					if (i + offsetX >= 0 && i + offsetX < 8 && j + offsetY >= 0 && j + offsetY < 8 && board[i][j].type == 10 && board[i + offsetX][j + offsetY].type == turn) {
						found = true;
						break;
					}
				}
			}
			result[i][j] = found;
		}
	}
}