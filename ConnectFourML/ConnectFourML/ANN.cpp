#include "ANN.h"


ANN::ANN()
{
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

	net.set_activation_steepness_hidden(1.0);
	net.set_activation_steepness_output(1.0);

	net.set_activation_function_hidden(FANN::SIGMOID_STEPWISE);
	net.set_activation_function_output(FANN::SIGMOID_STEPWISE);

}

ANN::ANN(unsigned int layers, unsigned int inputs,  unsigned int hidden, unsigned int outputs, float learning)
{
	// net variables
	const unsigned int numLayers = layers;
	const unsigned int numInputs = inputs;
	const unsigned int numHidden = hidden;
	const unsigned int numOutputs = outputs;

	const float learningRate = learning;

	net.create_standard(numLayers, numInputs, numHidden, numOutputs);
	net.set_learning_rate(learningRate);

	net.set_activation_steepness_hidden(1.0);
	net.set_activation_steepness_output(1.0);

	net.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC_STEPWISE);
	net.set_activation_function_output(FANN::SIGMOID_SYMMETRIC_STEPWISE);
	
/*
	FANN::training_data data;
	if (data.read_train_from_file("cFour.data"))
	{
		net.init_weights(data);
	}
	
	int test[84];
	fann_type* inp[84];
	fann_type* outp = 10;
	for (int i = 0; i < 84; i++)
	{
		test[i] = rand() % 2;
		inp[i] = test[i];
	}
	FANN::training_data data;
	data.set_train_data(1, 84, inp, 1, outp);
	data.set_train_data()
	net.init_weights(data);*/
}

ANN::~ANN()
{
	//net.destroy();
}

FANN::neural_net* ANN::getANN()
{
	return &net;
}
