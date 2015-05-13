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

	//net.create_standard(num_layers, num_input, num_hidden, num_output);

	//net.set_learning_rate(learning_rate);

	//net.set_activation_steepness_hidden(1.0);
	//net.set_activation_steepness_output(1.0);

	//net.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC_STEPWISE);
	//net.set_activation_function_output(FANN::SIGMOID_SYMMETRIC_STEPWISE);

}

//ANN::ANN(unsigned int inputs, unsigned int layers, unsigned int hidden, unsigned int outputs, float learning)
//{
	
//	// Net vatiables
//	const unsigned int numLayers = 3;
//	const unsigned int numInputs = 84;
//	const unsigned int numHidden = 250;
//	const unsigned int numOutputs = 1;
//
//	const float learningRate = 0.95f;
//
//	FANN::neural_net net;
//	net.create_standard(numLayers, numInputs, numHidden, numOutputs);
//	net.set_learning_rate(learningRate);
//
//}


ANN::~ANN()
{
	//net.destroy();
}
