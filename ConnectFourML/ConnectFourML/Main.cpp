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
	int play1Wins = 0,
		play2Wins = 0,
		play1TotalWins = 0,
		play2TotalWins = 0,
		play1RandWins = 0,
		play2RandWins = 0;
	// d
	//double p1NumWins = 0;
	//double p2NumWins = 0;
	//double p1NumWinMoves = 0;
	//double p2NumWinMoves = 0;



	int percentile = 0;
	double p1Percent[10];
	double p2Percent[10];
	std::stringstream str_allResults;
	str_allResults << "TrainStart TrainEnd WinPlay1 WinPlay2 WinPlay1Rand WinPlay2Rand\n";
	// d
	//std::stringstream stream_randGames;
	//std::stringstream str_results;
	//stream_randGames << "// LearnPlayWins RandPlayWins\n//Plays " << globals.randPlayAmount << " each test\n";
	//str_results << "TrainStart TrendEnd WinPlay1 WinPlay2\n";
	int game_range = globals.episodes / 10;

#pragma region Play_N_Games

	for (int i = 0; i < globals.episodes; i++)
	{
		// Training: 1000 games against random //

		// If on a multiple of episodes/10
		if (globals.isTraining && ((i+1)%(game_range) == 0)){
			// Play RandPlayer 1000 times //
			globals.playRandomPlayer = true;
			globals.isTraining = false;
			int learnWins = 0, randWins = 0;
			int game_range_upper = i + 1;
			int game_range_lower = game_range_upper - game_range ;
			game_range_upper--;
			for (int c = 0; c < globals.randPlayAmount; c++){
				Connect4Result result = ConnectFour();
				if (result.winner == 1) {
					learnWins++; 
					play1RandWins++; }
				else {
					randWins++;
					play2RandWins++;
				}
			}
			// d
			/*stream_randGames << "//" << game_range_lower << "-> " << game_range_upper<< "\n"
				<< learnWins << " "<< randWins << '\n';
			*/			
			str_allResults << game_range_lower << " " << game_range_upper << " " << play1Wins << " " << play2Wins << " " << learnWins << " " << randWins << "\n";
			play1Wins = 0;
			play2Wins = 0;

			std::ofstream tempAllResultsOut(globals.allResultsFile + "game_" + std::to_string(globals.gamesPlayed + 1) + ".txt", std::ofstream::ate);
			tempAllResultsOut << str_allResults.str();

			globals.playRandomPlayer = false;
			globals.isTraining = true;
		}

		// Play a game
		printf("Game: %i\n", i);

		try {
			Connect4Result result = ConnectFour();

			// Evaluate and store the result
			if (result.winner == 1)
			{
				play1Wins++;
				play1TotalWins++;
				//d 
				//p1NumWins++;
				//p1NumWinMoves += result.moves;
			}
			else if (result.winner == 2)
			{
				play2Wins++;
				play2TotalWins++;

				// d
				//p2NumWins++;
				//p2NumWinMoves += result.moves;
			}
			// d
			//if (globals.episodes >= 100)
			//{
			//	// if we have played a  multiple of 10% of the games, then store the win/loss ratios
			//	if ( (i+1) % (game_range) == 0){
			//		p1Percent[percentile] = p1NumWins / (p1NumWins + p2NumWins);
			//		p2Percent[percentile] = p2NumWins / (p1NumWins + p2NumWins);
			//		percentile++;

			//		if (globals.NN_LEARNRATE_DECAY_BOOL && globals.isTraining)
			//		{
			//			globals.NN_LEARNRATE_DECAY = 1.0 - ((i + 1) / game_range) * 0.1;
			//			float newLearnRate = globals.NN_LEARNRATE * globals.NN_LEARNRATE_DECAY;
			//			globals.net1->set_learning_rate(newLearnRate);
			//		}
			//	}
			//}
		}
		catch (const std::exception e){}
		globals.gamesPlayed++;
	}

#pragma endregion
	// Add totals to end of train_results.txt
	str_allResults << "0 " << globals.episodes - 1 << " " << play1TotalWins << " " << play2TotalWins
		<< " " << play1RandWins << " " << play2RandWins;
	// Print allResults to File
	std::ofstream allResultsOut(globals.allResultsFile + ".txt", std::ofstream::ate);
	allResultsOut << str_allResults.str();

	globals.net1->save(globals.netFile1 + ".net");
	// d
	//std::streambuf* cout_sbuf = std::cout.rdbuf();
	//std::ofstream fout(globals.randPlayFile + ".txt");
	//cout.rdbuf(fout.rdbuf());
	//std::cerr.rdbuf(fout.rdbuf());

#pragma region Print_Outcome
	// globals.net1->print_parameters();

	//double total_won_p1 = 0.0;
	//for (int i = 0; i < 10; i++){
	//	int game_range_lower = i * game_range;
	//	int game_range_upper = (i + 1) * game_range - 1;
	//	total_won_p1 += p1Percent[i];
	//	cout << "Games: " << game_range_lower << " -> " << game_range_upper << std::endl;
	//	cout << "P1: " << p1Percent[i] * 100 << "%" << std::endl;
	//	cout << "P2: " << p2Percent[i] * 100 << "%" << std::endl;
	//}	
	//total_won_p1 = total_won_p1 / 10;
	//double total_won_p2 = 1 - total_won_p1;
	//cout << "All Games: 0 -> " << globals.episodes << std::endl;
	//cout << "P1: " << total_won_p1 * 100 << "%" << std::endl;
	//cout << "P2: " << total_won_p2 * 100 << "%" << std::endl;
#pragma endregion


	/*system("pause");*/
	
	return 0;
}