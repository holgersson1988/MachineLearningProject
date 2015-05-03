#include<iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "MainHelper.h"
using std::cout;

char place[6][7];	// Declared in MainHelper.h

int main()
{
	// initialize random seed. Is global.
	srand(time(NULL));

	for(int a =0;a <= 5; a++){		//fill place with whitespace
		for(int b = 0; b<=6; b++)	
			place[a][b] = ' ';		
}								
	/* initialize two random players*/
	RandomPlayer play1 = RandomPlayer(CHAR1);
	RandomPlayer play2 = RandomPlayer(CHAR2);
	/*------------------------------*/	


	display();						//Displays for first time so players can see the board
	int hold;						//Will house user row choice
	int hold2 = 0;					//will hold drop value
	int charsPlaced = 0;			//Number of peices dropped so can end game if a draw
	bool gamewon = false;			//Will be changed to tdrue when game is won and will exit while loop
	Player* player = &play2;		//start as player 2 will change back 2 player 1
	while(!gamewon){				//will stop when game is won, ! means NOT makes the oppisite be checked
		if(hold2 != -1){			//check if there was a error in the last drop
			if(player->getPiece() == CHAR2){	//if player 2 lasted dropped a piece so its player 1s turn
				cout<<"player 1 drop where?";
				player = &play1;		//char of players piece
			}
			else{
				cout<<"player 2 drop where?";
				player = &play2;		//char of player piece
			}
		}
		// This loops until valid user input. Hold1 should be column choice
		hold = player->getMove();

		if (charsPlaced == 42) break;		//if draw
		hold2 = drop(hold,player->getPiece());			//drop the player store the row in hold2
		if(hold2 == -1)	cout<<"Column is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
		else{
			gamewon = check(hold2,hold);	//check if game is run
			charsPlaced ++;					//another character has been succesfully placed
			system("cls");					//This clears the screen works with windows, not nesscery to run game
			display();						//displayed updated board
		}
	}
	system("cls");							//this clears the screen
	if(charsPlaced == 42){					//if draw
		cout<<"No winner, Game was draw\n";
		system("pause");
		return 0;
	}
	if(player->getPiece() == CHAR2)						//if won by player 2
		cout<<"gamewon by : player 2\n";
	else cout<<"gamewon by : player 1\n";	//Else won by player 1
	system("pause");						//pauses before exit so players can see who won, works with windows
	return 0;								//Exit application
}
