#include <string>
#include <ios>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "MainHelper.h"
//Globals globals;

Globals globals;
int main(int argc, char* argv[])
{
	globals = Globals();
	// parse arguments
	for (int i = 0; i < argc; i++){
		// Display Board
		if (std::string(argv[i]) == "-d")
			globals.showBoard = true;
	}

	// initialize random seed. Is global.
	srand(time(NULL));

	//globals = Globals();

	/* Initialize NN
	unsigned int layers = 3;
	unsigned int inputs = 84;
	unsigned int num_nodes = 250;
	unsigned int outputs = 1;
	float nn_learn_rate = 0.3f;*/

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
			Connect4Result result = ConnectFour();

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
				if ( (i+1) % (game_range) == 0){
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

	// Print Stats to a file
	/*std::ofstream outputMoves("stats.txt");
	std::string sType = typeid(play1).name();
	cout << "Player1 (x) is " << sType << std::endl;
	sType = typeid(play2).name();
	cout << "Player2 (o) is " << sType << std::endl;
	outputMoves << 
	for (int i = 0; i < 7; i++)
	{
		
	}*/

	globals.net1->save(globals.netFile1);
	std::streambuf* cout_sbuf = std::cout.rdbuf();
	std::ofstream fout(globals.saveToFile);
	cout.rdbuf(fout.rdbuf());
	std::cerr.rdbuf(fout.rdbuf());

#pragma region Print_Outcome
	globals.net1->print_parameters();

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