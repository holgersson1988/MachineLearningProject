#pragma once
/*
 * Provides Q-learning methods for reinforcement learning. Allows
 * for function approximation using neural networks from the
 * open source FANN c++ neural network library
 *
 */
#include "floatfann.h"
#include "fann_cpp.h"

class QLearn {
public:
	FANN::neural_net net;


	/* 
	Default constructor 
	 */
	QLearn(){
		net = NULL;
	};


	/*
	 * Construct QLearn Object with a Neural Net.
	 */
	QLearn(FANN::neural_net &tNet) {
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

	// TODO
	// getQValue(NetState tState)

	/* TODO
	updateQValues(netState sequence[42]){
		// takes sequence of state-QValue pairs
		// sends to Neural Net to train

		net.train(stateSequence
	}
	*/
	};