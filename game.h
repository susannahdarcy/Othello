void printBoard(Token board[8][8], bool result[8][8], Player *player1, Player *player2);
void setup(Token board[8][8], Player *player1, Player *player2);
void play(Token board[8][8], Player *player1, Player *player2);
void broadCalculateMoves(bool result[8][8], Token board[8][8], bool turn);
int narrowCalculateMoves(bool result[8][8], bool boardResult[8][8],  Token board[8][8], bool turn);
void getMove(int move[2], Player currentPlayer, bool result[8][8]);
void playMove(int move[2], Token board[8][8], Player *currentPlayer, Player *otherPlayer, bool turn);
void saveToFile(Player *player1, Player *player2);