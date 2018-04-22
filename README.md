# Othello Description

## Assignment 2

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


Divided Work :
To work collaboratively we used GitHub for our main commiting of files. However to share our project we used GitLab.
We tried to split up the work evenly and we have ended up with similar code lines inputed. Alex Ng (Whose git name is Gnxela) first created the main file, and inputed his personal user input function, which we would use later to gather information from the user.
I (Susannah D'Arcy) then added the structures which will be the base for our program. Alex added more variables for the struct while adding libraries so we can include boolean and string functions.
We then moved onto the board which Alex created a function to print the board, I then zeroed (cleared the value in memory) the board layout, and created a function which will set up the board.
Alex then added the player set up and gathered the names through user input. I returned to the board and implement the initial board state, and created the play function, which will later be used for user's disk inputs, and it also prints the board.
We found a problem with how we set up the players, and decided a fix will be to use pointers, Alex implemented this change and extended the play function to suit pointers.
To finalized the project I added customizable tokens, which required new user input, new player struct variables, and changes to the board setup.
Lastly to divide the written elements on this project Alex documented the project and formatted our project. While I wrote this file detailing our project.

## Assignment 3

Broad:
To find all possible moves we decided to split it into 2 functions. Broad goes through each token on the board and checks to see if there is an emeny adjacent token.
This has been done by checking the surronding 8 squares with the use of offset Y and offset X. If an emeny token is found adjacent to a location, the locaton will be recorded in the results arrray. 
Narrow:
From the board function we narrow down the results to check to see if the board results locations are on a line with the current player token with any number of emeny tokens inbetween.
We have created a direction array, which holds all directions for the tile that we need to check. The function will check each location is all directions and if there is a sequence of emeny tokens terminating with the current token, if this holds, the location will be recorded in results.
Each result has been counted and count has been return to check if there was any possible moves.

Play Move:
Now that we have the all the possible moves, we ask the user which move they would like to use, and this will be used in our playMove function.
Play move uses the direction array to check each direction of the move and change emeny tokens with the current player's token, if the terminating token is the current players token.
With each token change the current players score will increment, while the other players score will decrement. 

Divided Work:
When you look at the commit distrbution for our project Alex has allot more lines commited than Susannah, this is due to though when Alex changed the formatting (from spaces into tabs), and pulled from git lab, this added a large amount of lines to his commit values. 
However the code itself has been split up evenly. We started project 3 by impleting the game rules for possible moves. To do this Alex first created the narrow move check. I then used his function to narrow down the results into the correct possible moves.
Alex implemented the requesting of moves from the user, I followed by adding more game rules, the flipping of tokens when the player places their token. Alex then added the scoring feature, and from this I created the end game rules, and outputed those scores to a file.
We then split up the tidying and commenting of our code, and Alex moved the saving scores to a file into a function. After we finished cleaning up and commenting the code, seeing as I previously wrote this file, I continued for this project.