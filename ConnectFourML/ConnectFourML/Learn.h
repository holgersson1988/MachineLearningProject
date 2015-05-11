#pragma once
/*
 * Provides Q-learning methods for reinforcement learning. Allows
 * for function approximation using neural networks from the
 * open source FANN c++ neural network library
 *
 */
#include "floatfann.h"
#include "fann_cpp.h"

/*
 * Saves State, Value, and Reward tuples for generating a training sequence
 * for the neural net.
 */
struct LearnTuple
{
	bool* state;
	float value;
	int reward;
	
	LearnTuple(){};

	LearnTuple(bool* tState, float tValue, int tReward){
		state = tState;
		value = tValue;
		reward = tReward;
	}


};

class Learn {
public:
	static FANN::neural_net net;
	static LearnTuple learnTrainSequence[42];


	/* 
	Default constructor 
	 */
	Learn(){
		net = NULL;
	};


	/*
	 * Construct Learn Object with a Neural Net.
	 */
	Learn(FANN::neural_net &tNet) {
		net = tNet;
		// Net properties should outside of this function.
	}


	/* 
	 * Assigns the Neural Network used for approximating the Q-Value function.
	 */
	void setNet(FANN::neural_net &tNet){
		net = tNet;
	}
	
	/*
	 * Convert Game state[a][b] to a bit string for input to the ANN
	 */
	bool* getInput(char**);

	
	/*
	 * Called by LearnPlayer. Returns a next state choice, from a greedy
	 * or exploration choice.
	 */
	int nextState();
	

	/*
	updateValues(){
		// takes global sequence of state-QValue pairs
		// sends to Neural Net to train

		net.train(stateSequence
	}
	*/
	};