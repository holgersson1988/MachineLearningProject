#include "MainHelper.h"
#include <string>
#include <ios>
#include <cstdlib>
#include <iostream>
#include <iomanip>

int main(int argc, char* argv[])
{
	// parse arguments
	bool showBoard = false, loadNet = true;
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
	unsigned int num_nodes = 250;
	unsigned int outputs = 1;
	float nn_learn_rate = 0.1f;
	ANN ArtificialNeuralNet = ANN(layers, inputs, num_nodes, outputs, nn_learn_rate);
	FANN::neural_net* net = ArtificialNeuralNet.getANN();
	if (loadNet){
		net->create_from_file(netFile);
	}

	// Stats to save
	int numGames = 2000;
	double p1NumWins = 0;
	double p2NumWins = 0;
	double p1NumWinMoves = 0;
	double p2NumWinMoves = 0;

	int percentile = 0;
	double p1Percent[10];
	double p2Percent[10];

	for (int i = 0; i < numGames; i++)
	{
		// Play a game
		Connect4Result result = ConnectFour(showBoard, net);

		// Evaluate and store the result
		if (result.winner == 1)
		{
			p1NumWins++;
			p1NumWinMoves += result.moves;
		}
		else if (result.winner == 2)
		{
			p2NumWins++;
			p2NumWinMoves += result.moves;
		}
		// if we have played a multiple of 10% of the games, then store the win/loss ratios
		if (i % (numGames / 10) == (numGames / 10) - 1)
		{
			cout << "\n\n\n\n\n\n\n\n\n";

			p1Percent[percentile] = p1NumWins / (p1NumWins + p2NumWins);
			p2Percent[percentile] = p2NumWins / (p1NumWins + p2NumWins);
			percentile++;
		}
	}

	std::cout << "P1    P2\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << p1Percent[i] * 100 << "%    " << p2Percent[i] * 100 << "%\n";
	}

	// Save NN
	net->save(netFile);
	system("pause");
	return 0;

}