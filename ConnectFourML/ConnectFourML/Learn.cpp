#pragma once
#include "Learn.h"

using std::cout;
using std::vector;


TrainPair::TrainPair(vector<fann_type> tState, fann_type tValue){
	state = tState;
	value = tValue;
}

Learn::Learn(){

	explore = 0.95f;
	decay = 0.95f;
	learnFactor = globals.RL_LEARNFACTOR;
	gameOver = false;
}
/**/
Learn::Learn(FANN::neural_net* tNet) {
	net = tNet;
	explore = 0.95f;
	decay = 0.95f;
	learnFactor = globals.RL_LEARNFACTOR;
	gameOver = false;
};

/*
 * Returns a bitstring to use as input for the ANN from the gameState array in Connect 4
 * 0 1 represents current player. We always want to represent the player who is choosing
 * a move as the same 'input' sequence to the array. Because of this, both player1 and
 * player2 represent themselves as '0 1' to the neural net.
 */
vector<fann_type> Learn::getInput(vector<vector<char>> &gameState)
{
	// Create return array
	//bool* ret = new bool[84];

	vector<fann_type> inputArray(84, 0.0);
	char curPlayer = player->getPiece();
	// Loop through the game board
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			// Get the char at each slot on the board
			char val = gameState[y][x];
			if (val == CHAR1 || val == CHAR2)
			{
				int returnIndex = y * 14 + x * 2;

				if (val == curPlayer)
					returnIndex++;

				inputArray[returnIndex] = 1.0;
			}


			// Check for player 1
			//if ((y*x) % 2 == 0)
			//{
			//	if (val == CHAR1)
			//	{
			//		inputArray[returnIndex] = true;
			//	}
			//	else
			//	{
			//		inputArray[returnIndex] == false;
			//	}
			//}
			//// Check for player 2 char
			//else
			//{
			//	if (val == CHAR2)
			//	{
			//		inputArray[returnIndex] = true;
			//	}
			//	else
			//	{
			//		inputArray[returnIndex] == false;
			//	}
			//}
		}
	}
	return inputArray;
}

/*
* Called by LearnPlayer. Returns a next state choice, from a greedy
* or exploration choice. Also updates learnTrainSequence with choice.
*/
LearnTuple Learn::nextState(int &moveChoice){
	float bestValue = -2;	// Saves values of greedy choice
	int depth;
	vector<fann_type> fannInput;
	vector<vector<char>> nextPlace;	// Place holder for next state. Presented to net for Value. 
	float randValue = ((float)rand()) / (float)RAND_MAX;
	vector<int> ties;

	vector<LearnTuple> states_values;
	states_values.resize(7, LearnTuple());

	// Greedy
	if (randValue < explore)
	{
		vector<int> stateValue = vector<int>(7, -1);		// Holds Values of next 7 possible state

		for (int i = 0; i < 7; i++)
		{
			depth = getMoveDepth(i);

			// If move was valid:
			if (depth > 0){
				nextPlace = place;
				nextPlace[depth][i] = player->getPiece();
				fannInput = getInput(nextPlace);
				states_values[i].setValue(  net->run(&fannInput[0])[0]  );
				states_values[i].setState(fannInput);

				// if this state value is greater than previous known best
				// Saves best: state, choice, and value
				if (states_values[i].getValue() > bestValue){
					moveChoice = i;
					bestValue = states_values[i].getValue();
				}
			}


		}
		//bestState = tempBestState;
		// Find tie indices
		for (int i = 0; i < 7; i++){
			if (states_values[i].getValue() == bestValue)
				ties.push_back(i);
		}

		// More than 1 state has bestValue
		if (ties.size() > 1){
			int tieBreaker = rand() % ties.size();
			moveChoice = ties[tieBreaker];
		}

	}

	// Explore (randValue > exploreValue)
	else
	{
		depth = -1;
		while (depth == -1)
		{
			moveChoice = rand() % 7;
			depth = getMoveDepth(moveChoice);
		}
		nextPlace = place;
		nextPlace[depth][moveChoice] = player->getPiece();
		fannInput = getInput(nextPlace);
		states_values[moveChoice].setState(  fannInput  );
		states_values[moveChoice].setValue(  net->run(&fannInput[0])[0]  );
	}

	// Save bestState, Value, and reward to learnTrainSequence
	return states_values[moveChoice];
}

/*
 * Updates Learn.trainSet to create (state, value) pairs with which we
 * train the ANN. Uses the standard TD reinforcement algo:
 * V(s) <- V(s) + n[ R + decay * V(s') - V(s)]
 */
void Learn::updateTrainSet(vector<LearnTuple> learnSequence){
	vector<LearnTuple> pas = learnSequence; // pas stands for 'Player Action Sequence'
	int pas_size = pas.size();
	int exp = 0;
	fann_type newV;
	// for reverse_iterator, ++ moves the index towards 0.
	for (vector<LearnTuple>::reverse_iterator rit = pas.rbegin(); 
		rit != pas.rend(); rit++)
	{
		float v_s = rit->value; // V(s)
		float v_s_p;			// V(s')
		int reward = rit->reward;

		// If updating the player's final choice. Don't want V(s')
		if (exp == 0)
			v_s_p = 0;
		else{
			/*v_s_p = (rit - 1)->getValue();*/
			v_s_p = newV;
		}
		newV = v_s + learnFactor * (reward + decay * v_s_p - v_s);
		TrainPair pair = TrainPair(rit->state, newV);
		trainSet.push_back(pair);
		exp++;
	}
	int setSize = trainSet.size();
	// debug
	// printf("<<<<<<<<<<<<<<<<<<<<<<< Learn::updateTrainSet() trainSet.size(): %i \n", setSize);
	}
/*
 * Calls getTrainData and then trains ANN.
 */
void Learn::endGame(){

	// endGame() has already been called
	if (gameOver != true)
	{
		gameOver = true;
		// TODO
		// Send train set to the ANN
		unsigned int num_data, num_input = 84, num_output = 1;
		num_data = static_cast<int>(trainSet.size());
		FANN::training_data data;

		
		vector<float*> inputDataContainer;
		vector<float*> outputDataContainer;
		for (unsigned int j = 0; j < num_data; j++)
		{
			float* inputData = new float[84];
			for (int i = 0; i < 84; i++)
			{
				inputData[i] = (trainSet[j].getState()[i]);
			}
			inputDataContainer.push_back(inputData);

			float* outputData = new float[1];
			outputData[0] = (trainSet[j].getValue());
			outputDataContainer.push_back(outputData);
		}

		//data.set_train_data()
		data.set_train_data(num_data, num_input, 
			&inputDataContainer[0], num_output, &outputDataContainer[0]);

////// Pre Train Values ///////////////////////////////////////////
		//for (unsigned int i = 0; i < data.length_train_data(); ++i)
		//{
		//	// Run the network on the test data
		//	fann_type *calc_out = net->run(data.get_input()[i]);

		//	cout << "C4 test (" << std::showpos << i << ") -> " << *calc_out
		//		<< ", should be " << data.get_output()[i][0] << ", "
		//		<< "difference = " << std::noshowpos
		//		<< fann_abs(*calc_out - data.get_output()[i][0]) << std::endl;
		//}
/////////////////////////////////////////////////////////////

		net->train_on_data(data, 1000, 100, 0.001f); // TODO - Decide epochs

////// Post Train Values ///////////////////////////////////////////
		//for (unsigned int i = 0; i < data.length_train_data(); ++i)
		//{
		//	// Run the network on the test data
		//	fann_type *calc_out = net->run(data.get_input()[i]);

		//	cout << "C4 test (" << std::showpos << i << ") -> " << *calc_out
		//		<< ", should be " << data.get_output()[i][0] << ", "
		//		<< "difference = " << std::noshowpos
		//		<< fann_abs(*calc_out - data.get_output()[i][0]) << std::endl;
		//}
/////////////////////////////////////////////////////////////

		for (unsigned int i = 0; i < inputDataContainer.size(); i++){
			delete inputDataContainer[i];
			delete outputDataContainer[i];
		}
		data = FANN::training_data();
	}
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