#pragma once
#include "Learn.h"

using std::cout;
using std::vector;

TrainPair::TrainPair(fann_type* tState, fann_type tValue){
	state = tState;
	value = tValue;
}

Learn::Learn(){

	explore = 0.95;
	decay = 0.95;
	learnRate = 0.95;
	gameOver = false;
}
/**/
Learn::Learn(FANN::neural_net* tNet) {
	net = tNet;
	explore = 0.95;
	decay = 0.95;
	learnRate = 0.95;
	gameOver = false;
};

/*
 * Returns a bitstring to use as input for the ANN from the gameState array in Connect 4
 */
fann_type* Learn::getInput(vector<vector<char>> &gameState)
{
	// Create return array
	//bool* ret = new bool[84];

	fann_type inputArray[84];
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
LearnTuple Learn::nextState(int &moveChoice){
	float moveValue = -2;	// Saves values of greedy choice
	fann_type* netState;			// for saving the state in NN form
	vector<vector<char>> nextPlace;	// Place holder for next state. Presented to net for Value. 
	float randValue = ((float)rand()) / (float)RAND_MAX;

	fann_type fannInput[84];
	// Greedy
	if (randValue < explore)
	{
		vector<int> stateValue = vector<int>(7, -1);		// Holds Values of next 7 possible state

		for (int i = 0; i < 7; i++)
		{
			int moveDepth = getMoveDepth(i);

			// If move was valid:
			if (moveDepth > 0)
			{
				nextPlace = place;
				nextPlace[moveDepth][i] = player->getPiece();
				fann_type *inputArray = getInput(nextPlace);
				//bool* neuralState = getInput(nextPlace);
				// Convert the boolean string to type: "fann_type"
				for (int f = 0; f < 84; f++)
				{
					fannInput[f] = inputArray[f];
				}

				stateValue[i] = net->run(fannInput)[0];
				if (stateValue[i] > moveValue)
				{
					moveChoice = i;
					netState = inputArray;
					moveValue = stateValue[i];
				}
			}
		}

		// Select between ties
		std::vector<int> ties;
		int numTies = 0;
		for (int i = 0; i < 7; i++)
		{
			// For each tie, save its index in the vector
			if (stateValue[i] == stateValue[moveChoice])
			{
				ties.push_back(i);
				numTies++;
			}
		}
		// Select a random winner from the vector of ties
		int winner = rand() % numTies;
		// Get the value from the vector that represents the choice made
		moveChoice = ties[winner];

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
		moveValue = 1; // temporary until net works
	}

	// Save netState, Value, and reward to learnTrainSequence
	LearnTuple returnTuple(netState, moveValue, 0);
	return returnTuple;
}

/*
 * Returns a sequence of TrainPairs' used to train the ANN. Uses
 * the reinforcement learning update algorithm.
 */

/*
 * Updates Learn.trainSet to create (state, value) pairs with which we
 * train the ANN. Uses the standard TD reinforcement algo:
 * V(s) <- V(s) + n[ R + decay * V(s') - V(s)]
 */
void Learn::updateTrainSet(vector<LearnTuple> learnSequence){
	vector<LearnTuple> pas = learnSequence; // pas stands for 'Player Action Sequence'
	
	int exp = 0;
	// for reverse_iterator, ++ moves the index towards 0.
	for (vector<LearnTuple>::reverse_iterator rit = pas.rbegin(); rit != pas.rend(); rit++){
		float v_s = rit->value; // V(s)
		float v_s_p;			// V(s')
		int reward = rit->reward;

		// If updating the player's final choice. Don't want V(s')
		if (exp == 0)
			v_s_p = 0;
		else{
			v_s_p = (rit - 1)->value;
		}

		fann_type newV = v_s + learnRate * (reward + decay * v_s_p - v_s);
		TrainPair pair = TrainPair(rit->state, newV);
		trainSet.push_back(pair);
	}
}

/*
 * Calls getTrainData and then trains ANN.
 */
void Learn::endGame(){

	// endGame() has already been called
	if (gameOver == true){}
	else{
		gameOver == true;
		// TODO
		// Send train set to the ANN
		for (int i = 0; i < trainSet.size(); i++)
		{
			net->train(trainSet[i].state, &trainSet[i].value);
		}

	}
	
	return;
}


void trainSetToString(vector<TrainPair> &tSet, std::string &string){
	// numPairs 84 1
	std::stringstream stream;
	stream << tSet.size() << " 84 1\n";
	for (std::vector<TrainPair>::iterator it = tSet.begin(); it != tSet.end(); it++){
		// 0 1 0 0 0 1 0 1 1 0 1 1 0 1 1 ...
		for (int i = 0; i < 84; i++){
			stream << it->getState()[i] ? "1" : "0";
			stream << ' '; 
		}
		stream << '\n';
		// 0.89
		stream << it->getValue() << '\n';

	}
	string = stream.str();
}