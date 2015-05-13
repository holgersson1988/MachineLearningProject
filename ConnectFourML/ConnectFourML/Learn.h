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
using std::cout;
using std::vector;

/*
 * Saves State, Value, and Reward tuples for generating a training sequence
 * for the neural net.
 */
struct LearnTuple
{
	bool* state;
	float value;
	int reward;
	
	LearnTuple(){}

	LearnTuple(bool* tState, float tValue, int tReward);

	void setReward(int r) { reward = r; }

};

/*struct TrainPair {
	bool* state;
	float value;

	// Constructors
	TrainPair();
	TrainPair(bool* tState, float tValue);

	void setValue(float tValue) { value = tValue; }
	void setState(bool* tState) { state = tState; }
};*/

/*
 * Learn Class used for Sarsa/TD style reinforcement learning. Uses a 
 * FANN neural net to approximate the Value of states.
 */
class Learn {
public:
	//static FANN::neural_net net;
	vector<LearnTuple> learnSequence;
	float explore;
	float decay;

	/* 
	Default constructor 
	 */
	Learn();

	/*
	 * Construct Learn Object with a Neural Net.
	 */
	//Learn(FANN::neural_net &tNet);

//	void setNet(FANN::neural_net &tNet){ net = tNet; };
	void setDecay(float tDecay);
	void setExploration(float tExploration);
	
	/*
	 * Convert Game state[a][b] to a bit string for input to the ANN
	 */
	bool* getInput(vector< vector<char> > &gameState);

	
	/*
	 * Called by LearnPlayer. Returns a next state choice, from a greedy
	 * or exploration choice.
	 */
	int nextState();
	void hasWon();
	//vector<TrainPair> getTrainData();
	void train();
};