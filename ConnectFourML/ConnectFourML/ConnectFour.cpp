#include <iostream>
#include <string>
#include <cstdlib>
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

int main(int argc, char* argv[])
{
	// parse arguments
	bool showBoard = false;
	for (int i = 0; i < argc; i++){
		if (std::string(argv[i]) == "-d")
			showBoard = true;
	}
	/*
#pragma region Create Artificial Neural Network

	FANN::neural_net net;
	// Net vatiables
	int numLayers = 3;
	int numInputs = 84;
	int numHidden = 250;
	int numOutputs = 1;

	double learningRate = 0.95;

	net.create_standard(numLayers, numInputs, numHidden, numOutputs);
	net.set_learning_rate(learningRate);

	net.set_activation_steepness_hidden(1.0);
	net.set_activation_steepness_output(1.0);
	net.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC_STEPWISE);
	net.set_activation_function_output(FANN::LINEAR);//SIGMOID_SYMMETRIC_STEPWISE?
	
	//net.train(FANN::training_data())

#pragma endregion
*/
	// initialize random seed. Is global.
	srand(time(NULL));

	
	// fill place with whitespaces
	place.resize(6, vector<char>(7, ' '));


	// Initialize LearnObject
	//Learn learnObj = Learn();

	// initialize two random players
	LearnPlayer play1 = LearnPlayer(CHAR1);
	LearnPlayer play2 = LearnPlayer(CHAR2);



	std::vector<MoveDepth> gameSequence;
	int colChoice;					// Will house user row choice
	int depthChoice = 0;			// Will hold drop value
	charsPlaced = 0;
	bool gamewon = false;
	int moveHistory[42];
	player = &play2;		//start as player 2, will change back to player 1


	// Main game loop
	while (!gamewon && charsPlaced < 42){
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
		gameSequence.push_back(MoveDepth(depthChoice, colChoice, player->getPiece()));
		//r// system("cls");						//This clears the screen works with windows, not nesscery to run game
	
	// End of main game loop
	}


	// End of game

	// Tie
	if (charsPlaced == 42)
		cout << 0 << ',' << charsPlaced << "\n";
	else{
		// Player 2 Won
		if (player->getPiece() == CHAR2){
			cout << 2 << ',' << charsPlaced << "\n";
			play2.hasWon();
			play1.hasLost();
		}
		// Player 1 won
		else{
			cout << 1 << ',' << charsPlaced << "\n";
			play1.hasWon();
			play2.hasLost();
		}
	}
	// Tell Learn that it can update NN
	play1.endGame();
	play2.endGame();

	// Display board if display flag (-d)
	if (showBoard){
		displaySequence(gameSequence);
	}
		
	system("pause");

	return 0;
}
