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
	// parse arguments
	for (int i = 0; i < argc; i++){
		// Display Board
		if (std::string(argv[i]) == "-d")
			globals.showBoard = true;
	}

	globals = Globals();

	// initialize random seed. Is global.
	srand(time(NULL));

	//globals = Globals();

	// Stats to save
	double p1NumWins = 0;
	double p2NumWins = 0;
	double p1NumWinMoves = 0;
	double p2NumWinMoves = 0;

	int percentile = 0;
	double p1Percent[10];
	double p2Percent[10];
	std::stringstream stream_randGames;
	stream_randGames << "// LearnPlayWins RandPlayWins\n//Plays " << globals.randPlayAmount << " each test\n";
	int game_range = globals.episodes / 10;

#pragma region Play_N_Games

	for (int i = 0; i < globals.episodes; i++)
	{
		// Training: 1000 games against random //
		if (globals.isTraining && ((i+1)%(game_range) == 0)){
			globals.playRandomPlayer = true;
			globals.isTraining = false;
			int learnWins = 0, randWins = 0;
			int game_range_upper = i + 1;
			int game_range_lower = game_range_upper - game_range;

			for (int c = 0; c < globals.randPlayAmount; c++){
				Connect4Result result = ConnectFour();
				(result.winner == 1) ? learnWins++: randWins++;
			}
			stream_randGames << "//" << game_range_lower << "-> " << game_range_upper<< "\n"
				<< learnWins << " "<< randWins << '\n';
			
			
			globals.playRandomPlayer = false;
			globals.isTraining = true;
		}
		
		/////////////////////////////////////////


		// Play a game
		printf("Game: %i\n", i);

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
			if (globals.episodes >= 100)
			{
				// if we have played a  multiple of 10% of the games, then store the win/loss ratios
				if ( (i+1) % (game_range) == 0){
					p1Percent[percentile] = p1NumWins / (p1NumWins + p2NumWins);
					p2Percent[percentile] = p2NumWins / (p1NumWins + p2NumWins);
					percentile++;

					if (globals.NN_LEARNRATE_DECAY_BOOL && globals.isTraining)
					{
						globals.NN_LEARNRATE_DECAY = 1.0 - ((i + 1) / game_range) * 0.1;
						float newLearnRate = globals.NN_LEARNRATE * globals.NN_LEARNRATE_DECAY;
						globals.net1->set_learning_rate(newLearnRate);
					}
				}
			}
		}
		catch (const std::exception e){}
		globals.gamesPlayed++;
	}

#pragma endregion

	// Print Stats to a file
	
	// Print randPlayStats to File
	std::ofstream randPlayOut(globals.saveRandPlay + ".txt", std::ofstream::ate);
	randPlayOut << stream_randGames.str();

	globals.net1->save(globals.netFile1 + ".net");
	std::streambuf* cout_sbuf = std::cout.rdbuf();
	std::ofstream fout(globals.saveToFile + ".txt");
	cout.rdbuf(fout.rdbuf());
	std::cerr.rdbuf(fout.rdbuf());

#pragma region Print_Outcome
	globals.net1->print_parameters();

	double total_won_p1 = 0.0;
	for (int i = 0; i < 10; i++){
		int game_range_lower = i * game_range;
		int game_range_upper = (i + 1) * game_range - 1;
		total_won_p1 += p1Percent[i];
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