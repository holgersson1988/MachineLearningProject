#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "MainHelper.h"
using namespace std;

char place[6][7];	// Declared in MainHelper.h

int main(int argc, char* argv[])
{
	// parse arguments
	bool showBoard = false;
	for (int i = 0; i < argc; i++){
		if (string(argv[i]) == "-d"){
			showBoard = true;
		}
	}

	// initialize random seed. Is global.
	srand(time(NULL));

	//fill place with whitespaces
	for(int a =0;a <= 5; a++){		
		for(int b = 0; b<=6; b++)	
			place[a][b] = ' ';		
}								
	// initialize two random players
	RandomPlayer play1 = RandomPlayer(CHAR1);
	RandomPlayer play2 = RandomPlayer(CHAR2);



	//r// display();						
	int hold;						//Will house user row choice
	int hold2 = 0;					//will hold drop value
	int charsPlaced = 0;			
	bool gamewon = false;			
	int moveHistory[42];
	Player* player = &play2;		//start as player 2, will change back 2 player 1


	// Main game loop
	while(!gamewon){	
		// Check if last getMove() returned valid move.
		if(hold2 != -1){			
			if(player->getPiece() == CHAR2){	//if player 2 lasted dropped a piece so its player 1s turn
				//r// cout<<"player 1 drop where?";
				player = &play1;
			}
			else{
				//r// cout<<"player 2 drop where?";
				player = &play2;
			}
		}
		
		// Get current player move
		hold = player->getMove();

		if (charsPlaced == 42) break;		//if draw
		hold2 = drop(hold,player->getPiece());			//drop the player store the row in hold2
		if (hold2 == -1);//r// cout << "Column is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
		else{
			moveHistory[charsPlaced] = hold;
			gamewon = check(hold2,hold);	//check if game is run
			charsPlaced ++;					//another character has been succesfully placed
			//r// system("cls");					//This clears the screen works with windows, not nesscery to run game
			//r// display();						//displayed updated board
			//r// system("pause");				//r// pauses for human readability
		}
	}
	//r// system("cls");							//this clears the screen
	//r// display();
	if(charsPlaced == 42){					//if draw
		//r//cout<<"No winner, Game was draw\n";
		cout << 0 << ',' << charsPlaced << "\n";
		system("pause");
		return 0;
	}
	if(player->getPiece() == CHAR2)						//if won by player 2
		//cout<<"game won by : player 2\n";
		cout << 2 << ',' << charsPlaced << "\n";
	else 
		// cout<<"game won by : player 1\n";	//Else won by player 1
		cout << 1 << ',' << charsPlaced << "\n";
	system("pause");						//pauses before exit so players can see who won, works with 

	// Display board if display is true
	if (showBoard){
		display();
	}
	system("pause");
	
	return 0;								//Exit application
}
