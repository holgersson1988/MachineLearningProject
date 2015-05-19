#pragma once
/*
 * Provides Q-learning methods for reinforcement learning. Allows
 * for function approximation using neural networks from the
 * open source FANN c++ neural network library
 *
 */

#include <iostream>
#include <vector>
#include "MainHelper.h"
#include "ANN.h"
using std::cout;
using std::vector;

struct TrainPair {
	bool* state;
	float value;

	// Constructors
	TrainPair();
	TrainPair(bool* tState, float tValue);

	void setValue(float tValue) { value = tValue; }
	void setState(bool* tState) { state = tState; }

	float getValue() { return value; };
	bool* getState() { return state; }
};

/*
 * Learn Class used for Sarsa/TD style reinforcement learning. Uses a 
 * FANN neural net to approximate the Value of states.
 */
class Learn 
{
public:
	FANN::neural_net* net;
	vector<TrainPair> trainSet;
	float explore;
	float decay;
	float learnRate;
	bool gameOver;


	/* 
	Default constructor 
	 */
	Learn();

	/*
	 * Construct Learn Object with a Neural Net.
	 */
	Learn(FANN::neural_net* tNet);

	void setNet(FANN::neural_net* tNet){ net = tNet; };
	void setDecay(float tDecay){ decay = tDecay; };
	void setExploration(float tExploration) { explore = tExploration; };

	
	/*
	 * Convert Game state[a][b] to a bit string for input to the ANN
	 */
	bool* getInput(vector< vector<char> > &gameState);

	
	/*
	 * Called by LearnPlayer. Returns a next state choice, from a greedy
	 * or exploration choice.
	 */
	LearnTuple nextState(int &move);
	
	void endGame();

	void updateTrainSet(vector<LearnTuple> learnSequence);

	void train();
};

/*
 * Transform the trainSet into file saveable string. 
 */
//void trainSetToString(vector<TrainPair> &tSet, std::string &string);