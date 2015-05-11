#pragma once
#include "Learn.h"
#include "MainHelper.h"

/*
Returns a bitstring to use as input for the ANN from the gameState array in Connect 4
*/
bool* Learn::getInput(char** gameState)
{
	bool* ret = new bool[84];

	for (int i = 0; i < 6; i++)
	{
		for (int ii = 0; ii < 7; ii++)
		{
			char val = gameState[i][ii];
			int returnIndex = i*ii; // 0*0=0, 1*0=0, 0*1=0 ???
			// Check for player 1
			if ((i*ii) % 2 == 0)
			{
				if (val == CHAR1)
				{
					ret[returnIndex] = true;
				}
				else
				{
					ret[returnIndex] == false;
				}
			}
			// Check for player 2 char
			else
			{
				if (val == CHAR2)
				{
					ret[returnIndex] = true;
				}
				else
				{
					ret[returnIndex] == false;
				}
			}
		}
	}
	return ret;
}

/*
* Called by LearnPlayer. Returns a next state choice, from a greedy
* or exploration choice. Also updates learnTrainSequence with choice.
*/
int Learn::nextState(){
	int moveChoice = -1;
	float moveValue = -1;	// Saves values of greedy choice
	bool* netState; // for saving the state in NN form
	

	// Explore or Greedy
	float randValue = ((float)rand()) / (float)RAND_MAX;
	// Greedy. 
	if (randValue < exploreValue){

		int stateValue[7];		// Holds Values of next 7 possible states
		char nextPlace[6][7];	// Place holder for next state
		bool* netInput;

		for (int i = 0; i < 7; i++)
		{
			int moveDepth = getMoveDepth(i);
			if (moveDepth > 0)
			{
				std::memcpy(nextPlace, place, sizeof (int)* 6 * 7);
				nextPlace[moveDepth][i] = player->getPiece();
				netInput = getInput(nextPlace); // No idea how to pass this TODO
				stateValue[i] = net.run(netInput)[0];
				if (stateValue[i] > greedyValue){
					moveChoice = i;
					netState = netInput;
				}
			}
			else
				stateValue[i] = -1;
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
		netState = getInput(nextPlace); // No idea how to pass this

	}

	// Save netState and Value to learnTrainSequence
	learnTrainSequence[charsPlaced] = LearnTuple(netState, moveValue, 0);

	// Return moveChoice
	return moveChoice;
}