#include "MainHelper.h"
#include "ANN.h"
#include "floatfann.h"
#include "fann_cpp.h"

using std::cout;

void testFANN(){

	// Create NN
	FANN::neural_net net;
	const float learning_rate = 0.7f;
	const unsigned int num_layers = 3;
	const unsigned int num_input = 2;
	const unsigned int num_hidden = 3;
	const unsigned int num_output = 1;
	const float desired_error = 0.001f;
	const unsigned int max_iterations = 300000;
	const unsigned int iterations_between_reports = 1000;

	std::cout << std::endl << "Creating network." << std::endl;

	net.create_standard(num_layers, num_input, num_hidden, num_output);

	net.set_learning_rate(learning_rate);

	//net.set_activation_steepness_hidden(1.0);
	//net.set_activation_steepness_output(1.0);

	net.set_activation_function_hidden(FANN::SIGMOID);
	net.set_activation_function_output(FANN::LINEAR);

	// Load data


	FANN::training_data data;
	if (data.read_train_from_file("myxor.data")){
		net.init_weights(data);


		fann_type *calc_out = net.run(data.get_input()[0]);
		cout << "XOR test (" << std::showpos << data.get_input()[0][0] << ", "
			<< data.get_input()[0][1] << ") -> " << *calc_out
			<< ", should be " << data.get_output()[0][0] << ", "
			<< "difference = " << std::noshowpos
			<< fann_abs(*calc_out - data.get_output()[0][0]) << std::endl;

		net.train_on_data(data, max_iterations, iterations_between_reports, desired_error);
		calc_out = net.run(data.get_input()[0]);
		cout << "XOR test (" << std::showpos << data.get_input()[0][0] << ", "
			<< data.get_input()[0][1] << ") -> " << *calc_out
			<< ", should be " << data.get_output()[0][0] << ", "
			<< "difference = " << std::noshowpos
			<< fann_abs(*calc_out - data.get_output()[0][0]) << std::endl;
	}
	// Run data
}
/*
bool* getInput(vector<vector<char>> &gameState)
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
			int returnIndex = ii + i * 7;
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
}*/