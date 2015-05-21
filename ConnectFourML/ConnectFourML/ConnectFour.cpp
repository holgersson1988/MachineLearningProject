#include <iostream>
#include <string>
#include <time.h>
#include "MainHelper.h"
#include "LearnPlayer.h"

//using std::cout;
//using std::vector;
//using std::string;

// Declared in MainHelper.h
vector< vector<char> > place;	
Player* player;
int charsPlaced;

int ConnectFour(bool showBoard, FANN::neural_net* net)
{

	std::vector<MoveDepth> gameSequence;
	int colChoice;					// Will house user row choice
	int depthChoice = 0;			// Will hold drop value
	charsPlaced = 0;
	bool gamewon = false;

//////////// fill place with whitespaces////////////////////////
	place.clear();
	place.resize(6, vector<char>(7, ' '));
////////////////////////////////////////////////////////////////

///////////// Initialize LearnObject. TODO: do this in Main ////
	float learn_decay = 0.7;
	float learn_learnRate = 0.7;
	Learn learnObj = Learn();
	learnObj.setNet(net);
	learnObj.setDecay(learn_decay);
	learnObj.setLearn(learn_learnRate);
////////////////////////////////////////////////////////////////

	// initialize two random players
	LearnPlayer* play1 = new LearnPlayer(CHAR1, &learnObj);
	LearnPlayer* play2 = new LearnPlayer(CHAR2, &learnObj);

	player = play2;		//start as player 2, will change back to player 1

	// Main game loop
	while (!gamewon && charsPlaced < 42){
		// Swap current player
		if (player->getPiece() == CHAR2)
			player = play1;
		else
			player = play2;

		// Get current player move
		// getMove() must only return legal move
		colChoice = player->getMove();
		// Break if game over
		if (charsPlaced == 42) break;
		depthChoice = drop(colChoice, player->getPiece());
		gamewon = check(depthChoice, colChoice);
		charsPlaced++;
		gameSequence.push_back(MoveDepth(depthChoice, colChoice, player->getPiece()));
		//r// system("cls");						//This clears the screen works with windows, not nesscery to run game

		// End of main game loop
	}

	// End of a game
	// Display board if display flag (-d)
	if (showBoard){
		displaySequence(gameSequence);
	}

	// Tie
	if (charsPlaced == 42)
		cout << 0 << ',' << charsPlaced << "\n";
	else{
		// Player 2 Won
		if (player->getPiece() == CHAR2){
			cout << 2 << ',' << charsPlaced << "\n";
			play2->hasWon();
			play1->hasLost();
		}
		// Player 1 won
		else{
			cout << 1 << ',' << charsPlaced << "\n";
			play1->hasWon();
			play2->hasLost();
		}
	}
	// Tell Learn that it can update NN
	play1->endGame();
	play2->endGame();

	return 0;
}
