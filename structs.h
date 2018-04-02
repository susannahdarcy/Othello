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
