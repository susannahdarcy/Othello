# Othello Description

Implementation:

Board:
We used a two dimensional array to represent the x and y values for the board.
We created the function setup, which will make all of the values for the board to be the empty tile, we then manually changed the tiles for the initial board set up.
To print the board the function print board was created, the board will show the value for each tile, and the number on the x and y axis express the location of each tile.
The board has a struct type of token, which will be used to change the values for each board tile. The board is printed by looping through each element of the two dimensional array.  
	

Disks/Token:
We used a struct for the disks, which have a value called type. The type depends on the colour/symbol of the disk, which is either true or false value.  This is used to distinguish between each disk. 
We decided for personalization sake to have the disks symbol to be inputed my the user, however which player start first will always be player 1.  To collect the symbols we use requestInput function, which only returns true for when the correct value is inputed, a single char.
The disk value will be added to the array representing the board, which changes which symbol to be printed. The number of disks and the placed disk are stored in our player struct, which allows us to have the count be for each player.
We use the token struct to identify the board, as the board is of the type 'Token'. Which means we the board elements are defined by the token type, and to input to the board we have to go through the token struct.

Players:
We also use a struct for the players. Each player will have the identity for their name and their token symbol.
The variable colour is used to distinguishes between the 2 different tokens. The struct will also keep count of the amount of token placed and the score for each player.
We have disks placed and score separate, as the token value can be flipped, but the amount of disks placed will not be changed. Score equals the amount of your disks which are on the board.
We collect the names of each players during the setup function. To collect the names we use requestInput function, which only returns true for when the correct value is inputed.


Divided Work:
To work collaboratively we used GitHub for our main commiting of files. However to share our project we used GitLab.
We tried to split up the work evenly and we have ended up with similar code lines inputed. Alex Ng (Whose git name is Gnxela) first created the main file, and inputed his personal user input function, which we would use later to gather information from the user.
I (Susannah D'Arcy) then added the structures which will be the base for our program. Alex added more variables for the struct while adding libraries so we can include boolean and string functions.
We then moved onto the board which Alex created a function to print the board, I then zeroed (cleared the value in memory) the board layout, and created a function which will set up the board.
Alex then added the player set up and gathered the names through user input. I returned to the board and implement the initial board state, and created the play function, which will later be used for user's disk inputs, and it also prints the board.
We found a problem with how we set up the players, and decided a fix will be to use pointers, Alex implemented this change and extended the play function to suit pointers.
To finalized the project I added customizable tokens, which required new user input, new player struct variables, and changes to the board setup.
Lastly to divide the written elements on this project Alex documented the project and formatted our project. While I wrote this file detailing our project.
