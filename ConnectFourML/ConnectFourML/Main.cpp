#include "MainHelper.h"
#include <string>
#include <ios>
#include <cstdlib>
#include <iostream>
#include <iomanip>

int main(int argc, char* argv[])
{
	// parse arguments
	bool showBoard = false, loadNet = false;
	std::string netFile = "tempNet.net";
	for (int i = 0; i < argc; i++){
		// Display Board
		if (std::string(argv[i]) == "-d")
			showBoard = true;
	}

	// initialize random seed. Is global.
	srand(time(NULL));

	// Initialize NN
	unsigned int layers = 3;
	unsigned int inputs = 84;
	unsigned int num_nodes = 30;
	unsigned int outputs = 1;
	float nn_learn_rate = 0.1;
	ANN ArtificialNeuralNet = ANN(layers, inputs, num_nodes, outputs, nn_learn_rate);
	FANN::neural_net* net = ArtificialNeuralNet.getANN();
	if (loadNet){
		net->create_from_file(netFile);
	}
	for (int i = 0; i < 1000; i++)
		ConnectFour(showBoard, net);
	// Save NN
	net->save(netFile);
	system("pause");
	return 0;

}