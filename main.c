#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Token {
	int type;	
} Token;

typedef struct Player {
	char name[20];
	bool colour;
	int tokensPlace;
} Player;

void printBoard(Token board[8][8]);
void setup(Token board[8][8]);


int main() {
	Token board[8][8];
	Player player1;
	Player player2;
	
	setup(board);
	printBoard(board);
}

void printBoard(Token board[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].type == 0) {
				printf("X ");
			} else if (board[i][j].type == 1) {
				printf("O ");
			} else {
				printf("_ ");
			}
		}
		printf("\n");
 	}
}

void setup(Token board[8][8]){
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j].type = 10;
			
		}
		
 	}
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