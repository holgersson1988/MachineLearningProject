#pragma once
/*
 * Provides Q-learning methods for reinforcement learning. Allows
 * for function approximation using neural networks from the
 * open source FANN c++ neural network library
 *
 */
#include "floatfann.h"
#include "fann_cpp.h"
class Learn {
public:
	FANN::neural_net net;
	netState gameSequence;


	/* 
	Default constructor 
	 */
	Learn(){
		net = NULL;
	};


	/*
	 * Construct QLearn Object with a Neural Net.
	 */
	Learn(FANN::neural_net &tNet) {
		net = tNet;
		// Net properties should outside of this function.
	}


	/* 
	Assigns the Neural Network used for approximating the Q-Value function.
	 */
	void setNet(FANN::neural_net &tNet){
		net = tNet;
	}
	
	/*
	 * Convert Game state[a][b] to a bit string for input to the ANN
	 */
	bool* getInput(char**);

	
	// TODO
	// updates gameSequence
	float getValue(int (&tStateValue)[7]);
	/* TODO 
	
	/*
	 * Convert Game state[a][b] to a bit string for input to the ANN
	 */
	bool* getInput(char**);

	updateValues(){
		// takes global sequence of state-QValue pairs
		// sends to Neural Net to train

		net.train(stateSequence
	}
	*/
	};