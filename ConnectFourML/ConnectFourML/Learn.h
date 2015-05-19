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
#include "floatfann.h"
#include "fann_cpp.h"
using std::cout;
using std::vector;

struct TrainPair {
	fann_type* state;
	fann_type value;

	// Constructors
	TrainPair();
	TrainPair(fann_type* tState, fann_type tValue);

	void setValue(fann_type tValue) { value = tValue; }
	void setState(fann_type* tState) { state = tState; }
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
	fann_type* getInput(vector< vector<char> > &gameState);

	
	/*
	 * Called by LearnPlayer. Returns a next state choice, from a greedy
	 * or exploration choice.
	 */
	LearnTuple nextState(int &move);
	
	void endGame();

	void updateTrainSet(vector<LearnTuple> learnSequence);

	void train();
};