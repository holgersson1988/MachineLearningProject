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
		if (string(argv[i]) == "-d")
			showBoard = true;
	}

	// initialize random seed. Is global.
	srand(time(NULL));

	// fill place with whitespaces
	for (int a = 0; a <= 5; a++){
		for (int b = 0; b <= 6; b++)
			place[a][b] = ' ';
	}
	// initialize two random players
	RandomPlayer play1 = RandomPlayer(CHAR1);
	RandomPlayer play2 = RandomPlayer(CHAR2);



	//r// display();						
	int colChoice;					//Will house user row choice
	int depthChoice = 0;			//will hold drop value
	int charsPlaced = 0;
	bool gamewon = false;
	int moveHistory[42];
	Player* player = &play2;		//start as player 2, will change back 2 player 1


	// Main game loop
	while (!gamewon){

		// Swap current player
		if (player->getPiece() == CHAR2)
			player = &play1;
		else
			player = &play2;

		// Get current player move
		// getMove() must only return legal move
		colChoice = player->getMove(); 

		// Break if game over
		if (charsPlaced == 42) break;
		depthChoice = drop(colChoice, player->getPiece());
		moveHistory[charsPlaced] = colChoice;
		gamewon = check(depthChoice, colChoice);	
		charsPlaced++;
		//r// system("cls");						//This clears the screen works with windows, not nesscery to run game
		//r// display();
	
	// End of main game loop
	}


	// End of game

	// Tie
	if (charsPlaced == 42)
		cout << 0 << ',' << charsPlaced << "\n";
	else{
		player->hasWon();
		// Player 2 Won
		if (player->getPiece() == CHAR2)
			cout << 2 << ',' << charsPlaced << "\n";
		// Player 1 won
		else
			cout << 1 << ',' << charsPlaced << "\n";
	}
	// Display board if display is true
	if (showBoard)
		display();
	system("pause");

	return 0;
}
