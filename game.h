void printBoard(Token board[8][8], bool result[8][8], Player *player1, Player *player2);
void setup(Token board[8][8], Player *player1, Player *player2);
void play(Token board[8][8], Player *player1, Player *player2);
void broadCalculateMoves(bool result[8][8], Token board[8][8], bool turn);
void narrowCalculateMoves(bool result[8][8], bool boardResult[8][8],  Token board[8][8], bool turn);
