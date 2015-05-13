#pragma once
#include "Learn.h"

using std::cout;
using std::vector;

<<<<<<< HEAD
TrainPair::TrainPair(bool* tState, float tValue){
=======
LearnTuple::LearnTuple(bool* tState, float tValue, int tReward){
	state = tState;
	value = tValue;
	reward = tReward;
}

/*TrainPair::TrainPair(bool* tState, float tValue){
>>>>>>> origin/ANN-Test
	state = tState;
	value = tValue;
}*/

Learn::Learn(){

	myNet = ArtificialNeuralNet.getANN();
	explore = 0.95;
	decay = 0.95;
	learnRate = 0.95;
	gameOver = false;
}
<<<<<<< HEAD
/**/
Learn::Learn(FANN::neural_net &tNet) {
	net = tNet;
	explore = 0.95;
	decay = 0.95;
	learnRate = 0.95;
	gameOver = 0.95;
};

=======

void Learn::setDecay(float tDecay)
{
	decay = tDecay;
}
void Learn::setExploration(float tExploration)
{
	explore = tExploration;
}
>>>>>>> origin/ANN-Test

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
<<<<<<< HEAD
LearnTuple Learn::nextState(int &moveChoice){
	float moveValue = -1;	// Saves values of greedy choice
	bool* netState;			// for saving the state in NN form
	vector<vector<char>> nextPlace;	// Place holder for next state. Presented to net for Value. 
	float randValue = ((float)rand()) / (float)RAND_MAX;
=======
int Learn::nextState()
{
	int moveChoice = -1;
	float moveValue = -1;	// Saves values of greedy choice
	bool* netState = false;			// for saving the state in NN form
	vector<vector<char>> nextPlace;	// Place holder for next 
	
	float randValue = ((float)rand()) / (float)RAND_MAX; // Generate random value to see if explore
>>>>>>> origin/ANN-Test

	fann_type fannInput[84];
	// Greedy
	if (randValue < explore)
	{
<<<<<<< HEAD
		vector<int> stateValue = vector<int>(7, -1);		// Holds Values of next 7 possible state
=======
		vector<int> stateValue = vector<int>(7, -1);		// Holds Values of next 7 possible states
		//bool* neuralState;
		//inputArray
>>>>>>> origin/ANN-Test

		for (int i = 0; i < 7; i++)
		{
			int moveDepth = getMoveDepth(i);

			// If move was valid:
			if (moveDepth > 0)
			{
				nextPlace = place;
				nextPlace[moveDepth][i] = player->getPiece();
<<<<<<< HEAD
				bool* neuralState = getInput(nextPlace);
				//stateValue[i] = net.run(neuralState)[0];
				stateValue[i] = 1; // <-- Temporary until net works
				if (stateValue[i] > moveValue)
				{
					moveChoice = i;

					// netState and moveValue will be saved in the LearnTuple
					netState = neuralState;
=======
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
>>>>>>> origin/ANN-Test
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
		moveValue = 1; // temporary until net works
	}

	// Save netState, Value, and reward to learnTrainSequence
<<<<<<< HEAD
	LearnTuple returnTuple(netState, moveValue, 0);
	return returnTuple;
=======
	learnSequence.push_back(LearnTuple(netState, moveValue, 0));

	// Return moveChoice
	return moveChoice;
>>>>>>> origin/ANN-Test
}

/*
 * Returns a sequence of TrainPairs' used to train the ANN. Uses
 * the reinforcement learning update algorithm.
 */

<<<<<<< HEAD
/*
 * Updates Learn.trainSet to create (state, value) pairs with which we
 * train the ANN. Uses the standard TD reinforcement algo:
 * V(s) <- V(s) + n[ R + decay * V(s') - V(s)]
 */
void Learn::updateTrainSet(vector<LearnTuple> learnSequence){
	vector<LearnTuple> pas = learnSequence;
	
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

		float newV = v_s + learnRate * (reward + decay * v_s_p - v_s);
		TrainPair pair = TrainPair(rit->state, newV);
		trainSet.push_back(pair);
	}
=======
vector<TrainPair> Learn::getTrainData()
{
	vector<TrainPair> blank;
	return blank;
>>>>>>> origin/ANN-Test
}

/*
 * Calls getTrainData and then trains ANN.
 */
<<<<<<< HEAD
void Learn::endGame(){

	// endGame() has already been called
	if (gameOver == true){ return; }
	else{

	}
	
=======
void Learn::hasWon()
{
	vector<TrainPair> trainSequence = getTrainData();
>>>>>>> origin/ANN-Test
}