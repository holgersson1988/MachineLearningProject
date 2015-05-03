
#include<iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "MainHelper.h"
using namespace std;

char place[6][7];	// Declared in MainHelper.h

int main()
{
	// initialize random seed. Is global.
	srand(time(NULL));

	for(int a =0;a <= 5; a++){		//fill place with whitespace
		for(int b = 0; b<=6; b++)	
			place[a][b] = ' ';		
}								
	display();						//Displays for first time so players can see the board
	int hold;						//Will house user row choice
	int hold2 = 0;					//will hold drop value
	int charsPlaced = 0;			//Number of peices dropped so can end game if a draw
	bool gamewon = false;			//Will be changed to true when game is won and will exit while loop
	char player = PLAY2;			//start as player 2 will change back 2 player 1
	while(!gamewon){				//will stop when game is won, ! means NOT makes the oppisite be checked
		if(hold2 != -1){			//check if there was a error in the last drop
			if(player == PLAY2){	//if player 2 lasted dropped a piece so its player 1s turn
				cout<<"player 1 drop where?";
				player = PLAY1;		//char of players piece
			}
			else{
				cout<<"player 2 drop where?";
				player = PLAY2;		//char of player piece
			}
		}
		while(true)
		{						//will run untill 'break;'
			if(charsPlaced == 42) break;	//if draw
			cin>>hold;						//get user input
			hold--;							//take off 1 to account for arrays starting at 0 not 1
			if(hold <=6 && hold>= 0) break;	//if within valid range stop loop
			else cout<< "\nplease enter a value between 1 and 7 :";//ask for input and loop again
			if (cin.fail())					//catch a non number
			{								//
				cin.clear();				//Stops cin trying to put its value in to hold
				char c;						//Try entering a non number without this, 2 see what this does
				cin>>c;						//
			}								//Catch a non number

		}
		if(charsPlaced == 42) break;		//if draw
		hold2 = drop(hold,player);			//drop the player store the row in hold2
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
	if(player == PLAY2)						//if won by player 2
		cout<<"gamewon by : player 2\n";
	else cout<<"gamewon by : player 1\n";	//Else won by player 1
	system("pause");						//pauses before exit so players can see who won, works with windows
	return 0;								//Exit application
}