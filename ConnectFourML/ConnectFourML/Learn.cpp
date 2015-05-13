#pragma once
#include "Learn.h"

using std::cout;
using std::vector;

LearnTuple::LearnTuple(bool* tState, float tValue, int tReward){
	state = tState;
	value = tValue;
	reward = tReward;
}

/*TrainPair::TrainPair(bool* tState, float tValue){
	state = tState;
	value = tValue;
}*/

Learn::Learn(){

	myNet = ArtificialNeuralNet.getANN();
	explore = 0.95;
	decay = 0.95;
}

void Learn::setDecay(float tDecay)
{
	decay = tDecay;
}
void Learn::setExploration(float tExploration)
{
	explore = tExploration;
}

/*
 * Returns a bitstring to use as input for the ANN from the gameState array in Connect 4
*/
bool* Learn::getInput(vector<vector<char>> &gameState)
{
	// Create return array
	//bool* ret = new bool[84];

	// Loop through the game board
	for (int i = 0; i < 6; i++)
	{
		for (int ii = 0; ii < 7; ii++)
		{
			// Get the char at each slot on the board
			char val = gameState[i][ii];
			int returnIndex = ii + i*7;
			// Check for player 1
			if ((i*ii) % 2 == 0)
			{
				if (val == CHAR1)
				{
					inputArray[returnIndex] = true;
				}
				else
				{
					inputArray[returnIndex] == false;
				}
			}
			// Check for player 2 char
			else
			{
				if (val == CHAR2)
				{
					inputArray[returnIndex] = true;
				}
				else
				{
					inputArray[returnIndex] == false;
				}
			}
		}
	}
	return inputArray;
}

/*
* Called by LearnPlayer. Returns a next state choice, from a greedy
* or exploration choice. Also updates learnTrainSequence with choice.
*/
int Learn::nextState()
{
	int moveChoice = -1;
	float moveValue = -1;	// Saves values of greedy choice
	bool* netState = false;			// for saving the state in NN form
	vector<vector<char>> nextPlace;	// Place holder for next 
	
	float randValue = ((float)rand()) / (float)RAND_MAX; // Generate random value to see if explore

	fann_type fannInput[84];
	// Greedy
	if (randValue < explore)
	{
		vector<int> stateValue = vector<int>(7, -1);		// Holds Values of next 7 possible states
		//bool* neuralState;
		//inputArray

		for (int i = 0; i < 7; i++)
		{
			int moveDepth = getMoveDepth(i);
			if (moveDepth > 0)
			{
				nextPlace = place;
				nextPlace[moveDepth][i] = player->getPiece();
				*inputArray = getInput(nextPlace);
				// Convert the boolean string to type: "fann_type"
				for (int f = 0; f < 84; f++)
				{
					fannInput[f] = inputArray[f];
				}

				stateValue[i] = myNet->run(fannInput)[0];
				if (stateValue[i] > moveValue)
				{
					moveChoice = i;
					netState = inputArray;
					moveValue = stateValue[i];
				}
			}
		}
	}

	// Explore (randValue > exploreValue)
	else
	{
		int depth = -1;
		while (depth == -1)
		{
			moveChoice = rand() % 7;
			depth = getMoveDepth(moveChoice);
		}
		nextPlace = place;
		nextPlace[depth][moveChoice] = player->getPiece();
		netState = getInput(nextPlace);
		// moveValue = net.run(netState)[0];
		moveValue = 1;
	}

	// Save netState, Value, and reward to learnTrainSequence
	learnSequence.push_back(LearnTuple(netState, moveValue, 0));

	// Return moveChoice
	return moveChoice;
}

/*
 * Returns a sequence of TrainPairs' used to train the ANN. Uses
 * the reinforcement learning update algorithm.
 */

vector<TrainPair> Learn::getTrainData()
{
	vector<TrainPair> blank;
	return blank;
}

/*
 * Calls getTrainData and then trains ANN.
 */
void Learn::hasWon()
{
	vector<TrainPair> trainSequence = getTrainData();
}