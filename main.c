#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "structs.h"
#include "input.h"
#include "game.h"

/**
 * Board type:
 * 	- 0:	Player 1 = X
 *  - 1:	Player 2 = O
 *	- Else:	Blank = _
 */


int main() {
	Token board[8][8];
	Player player1;
	Player player2;
	setup(board, &player1, &player2);
	play(board, &player1, &player2);
}

