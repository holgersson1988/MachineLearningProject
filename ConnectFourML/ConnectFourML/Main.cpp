#include <string>
#include <ios>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "MainHelper.h"
//Globals globals;

Globals globals;
int main(int argc, char* argv[])
{
	// parse arguments
	bool loadNet = false;

	for (int i = 0; i < argc; i++){
		// Display Board
		if (std::string(argv[i]) == "-d")
			globals.showBoard = true;
	}

	// initialize random seed. Is global.
	srand(time(NULL));


	/* Initialize NN
	unsigned int layers = 3;
	unsigned int inputs = 84;
	unsigned int num_nodes = 250;
	unsigned int outputs = 1;
	float nn_learn_rate = 0.3f;*/

	FANN::neural_net* net;
	ANN ArtificialNeuralNet = ANN(globals.NN_LAYERS, globals.NN_INPUTS, globals.NN_HIDDEN_NODES,
		globals.NN_OUPUTS, globals.NN_LEARNRATE);
	net = ArtificialNeuralNet.getANN();
	if (loadNet)
		net->create_from_file(globals.netLoadFile + ".txt");

	// Stats to save
	double p1NumWins = 0;
	double p2NumWins = 0;
	double p1NumWinMoves = 0;
	double p2NumWinMoves = 0;

	int percentile = 0;
	double p1Percent[10];
	double p2Percent[10];

	///////// Redirect cin //////////
	//	std::ofstream saveFile("saveFile.txt");
	//	std::streambuf *coutbuf = std::cout.rdbuf();
	//	std::cout.rdbuf(saveFile.rdbuf());
	//////////////////////////////////


#pragma region Play_N_Games

	for (int i = 0; i < globals.episodes; i++)
	{
		// Play a game
		printf("Game: %i\n", i);

		//std::streambuf* cout_sbuf = std::cout.rdbuf();
		//std::ifstream fake;
		//cout.rdbuf(fake.rdbuf());
		try {
			Connect4Result result = ConnectFour(net);

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
			if (globals.episodes > 100)
			{
				// if we have played a multiple of 10% of the games, then store the win/loss ratios
				int game_range = globals.episodes / 10;
				if (i % (game_range) == 0){
					p1Percent[percentile] = p1NumWins / (p1NumWins + p2NumWins);
					p2Percent[percentile] = p2NumWins / (p1NumWins + p2NumWins);
					percentile++;
				}
			}
		}
		catch (const std::exception e){}
		globals.gamesPlayed++;
	}

#pragma endregion


	net->save(globals.netLoadFile + ".txt");
	std::streambuf* cout_sbuf = std::cout.rdbuf();
	std::ofstream fout(globals.resultSaveFile + ".txt");
	cout.rdbuf(fout.rdbuf());
	std::cerr.rdbuf(fout.rdbuf());

#pragma region Print_Outcome
	net->print_parameters();

	double total_won_p1 = 0.0;
	for (int i = 0; i < 10; i++){
		total_won_p1 += p1Percent[i];
		int game_range = globals.episodes / 10;
		int game_range_lower = i * game_range;
		int game_range_upper = (i + 1) * game_range - 1;
		cout << "Games: " << game_range_lower << " -> " << game_range_upper << std::endl;
		cout << "P1: " << p1Percent[i] * 100 << "%" << std::endl;
		cout << "P2: " << p2Percent[i] * 100 << "%" << std::endl;
	}	
	total_won_p1 = total_won_p1 / 10;
	double total_won_p2 = 1 - total_won_p1;
	cout << "All Games: 0 -> " << globals.episodes << std::endl;
	cout << "P1: " << total_won_p1 * 100 << "%" << std::endl;
	cout << "P2: " << total_won_p2 * 100 << "%" << std::endl;
#pragma endregion


	system("pause");
	
	return 0;
}