#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Board type:
 * 	- 0:	Player 1 = X
 *  - 1:	Player 2 = O
 *	- Else:	Blank = _ 	
 */

typedef struct Token {
	int type;	
} Token;

typedef struct Player {
	char name[20];
	char token;
	bool colour;
	int tokensPlaced;
	int score;
} Player;

bool requestInput(int inputLength, char output[]);
void printBoard(Token board[8][8], Player *player1, Player *player2);
void setup(Token board[8][8], Player *player1, Player *player2);
void play(Token board[8][8], Player *player1, Player *player2);

int main() {
	Token board[8][8];
	Player player1;
	Player player2;
	
	setup(board, &player1, &player2);
	play(board, &player1, &player2);
}

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

void setup(Token board[8][8], Player *player1, Player *player2){
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
 * Reads a line from the console, handling errors and removing line endings.
 *
 * @param
 *  - inputLength: The max length of the input.
 *  - output: The inputted line is returned through this array.
 */
bool requestInput(int inputLength, char output[]) {
    if (fgets(output, inputLength, stdin)) {
        if (output[0] == '\n' || output[0] == '\0') {
            return false;
        } else {
            for (int i = 0; i < inputLength; i++) {//Loop through the list and find the first return carriage. Replace this with the null terminator.
                if (output[i] == '\n') {
                    output[i] = '\0';
                    break;
                }
            }
            return true;
        }
    } else {
        printf("We encountered an error reading input.");
        exit(1);
    }
    return false;
}

void play(Token board[8][8], Player *player1, Player *player2) {
	bool turn = false;
	while (true) {
		turn = !turn;
		Player currentPlayer = turn ? *player1 : *player2;
		printBoard(board, player1, player2);
		printf("%s's turn.\n", currentPlayer.name);
		printf("Tokens remaining: %d\n", 32 - currentPlayer.tokensPlaced);

		char input[20];
		printf("Enter input to continue.");
		requestInput(20, input);
	}
}