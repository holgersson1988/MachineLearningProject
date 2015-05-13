#pragma once
/*
 * Provides Q-learning methods for reinforcement learning. Allows
 * for function approximation using neural networks from the
 * open source FANN c++ neural network library
 *
 */

#include <iostream>
#include "MainHelper.h"
#include "floatfann.h"
#include "fann_cpp.h"
#include <vector>
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
	
	LearnTuple(){};

	LearnTuple(bool* tState, float tValue, int tReward){
		state = tState;
		value = tValue;
		reward = tReward;
<<<<<<< HEAD
	};
=======
	}
>>>>>>> parent of 0a704c8... Push before branch


};

<<<<<<< HEAD
=======
struct TrainPair {
	bool* state;
	float value;

	TrainPair(){}

	TrainPair(bool* tState, float tValue){
		state = tState;
		value = tValue;
	}

	void setValue(float tValue) { value = tValue; }
	void setState(bool* tState) { state = tState; }
};

>>>>>>> parent of 0a704c8... Push before branch
/*
 * Learn Class used for Sarsa/TD style reinforcement learning. Uses a 
 * FANN neural net to approximate the Value of states.
 */
class Learn {
public:
	static FANN::neural_net net;
<<<<<<< HEAD
	static LearnTuple learnSequence[42];
=======
	static vector<LearnTuple> learnSequence;
>>>>>>> parent of 0a704c8... Push before branch
	static float explore;
	static float decay;

	/* 
	Default constructor 
	 */
	Learn(){
		net = NULL;
		explore = 0.95;
		decay = 0.95;
	};


	/*
	 * Construct Learn Object with a Neural Net.
	 */
	Learn(FANN::neural_net &tNet) {
		net = tNet;
		explore = 0.95;
		decay = 0.95;
		// Net properties should outside of this function.
	};


	void setNet(FANN::neural_net &tNet){ net = tNet; };
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
	int nextState();
	

<<<<<<< HEAD
	/*
	updateValues(){
		// takes global sequence of state-QValue pairs
		// sends to Neural Net to train

		net.train(stateSequence
	}
	*/
=======
	void train();
>>>>>>> parent of 0a704c8... Push before branch
	};