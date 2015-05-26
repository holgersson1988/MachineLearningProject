#include <string>
#include <ios>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "MainHelper.h"

Globals globals;
int main(int argc, char* argv[])
{
	globals = Globals();

	// Error Check
	if (globals.error)
		return -1;

	// parse arguments
	for (int i = 0; i < argc; i++){
		// Display Board
		if (std::string(argv[i]) == "-d")
			globals.showBoard = true;
	}

	// initialize random seed. Is global.
	srand(time(NULL));

	// Stats to save
	int play1Wins = 0,
		play2Wins = 0,
		play1TotalWins = 0,
		play2TotalWins = 0,
		play1RandWins = 0,
		play2RandWins = 0,
		learnWins = 0,
		randWins = 0,
		moves = 0,
		totalMoves = 0,
		randMoves = 0,
		totalRandMoves = 0,
		avgMoves = 0,
		avgRandMoves = 0;

	int percentile = 0;
	double p1Percent[10];
	double p2Percent[10];
	std::stringstream str_allResults;
	str_allResults << "TrainStart TrainEnd WinPlay1 WinPlay2 WinPlay1Rand WinPlay2Rand avgTrainGameLength avgRandGameLength\n";
	if (globals.isCompetition)
		str_allResults << globals.play1Name << ' ' << globals.play2Name << '\n';
	else
		str_allResults << "LearnPlayer only" << '\n';

	int game_range = globals.episodes / 10;

#pragma region Play_N_Games

	for (int i = 0; i < globals.episodes; i++)
	{
		// Training: 1000 games against random //

		// If on a multiple of episodes/10
		if (((i + 1) % (game_range) == 0))
		{
			int learnWins = 0, randWins = 0;
			int game_range_upper = i + 1;
			int game_range_lower = game_range_upper - game_range;
			game_range_upper--;

			// Play RandPlayer 1000 times //
			if (globals.isTraining && !globals.isCompetition){
				globals.playRandomPlayer = true;
				globals.isTraining = false;

				for (int c = 0; c < globals.randPlayAmount; c++){
					Connect4Result result = ConnectFour();
					randMoves += result.moves;
					totalRandMoves += result.moves;
					if (result.winner == 1) {
						learnWins++;
						play1RandWins++;
					}
					else {
						randWins++;
						play2RandWins++;
					}
				}
				globals.playRandomPlayer = false;
				globals.isTraining = true;
				avgRandMoves = randMoves / game_range;
			}
			avgMoves = moves / game_range;

			str_allResults << game_range_lower << " " << game_range_upper << " " << play1Wins << " " << play2Wins 
								<< " " << learnWins << " " << randWins << " " << avgMoves << " " << avgRandMoves << "\n";
			std::ofstream tempAllResultsOut(globals.allResultsFile + "game_"
				+ std::to_string(globals.gamesPlayed + 1) + ".txt", std::ofstream::ate);

			play1Wins = 0;
			play2Wins = 0;
			learnWins = 0;
			randWins = 0;
			moves = 0;
			randMoves = 0;
			tempAllResultsOut << str_allResults.str();

		}

		// Play a game
		// printf("Game: %i\n", i);
		try {
			Connect4Result result = ConnectFour();
			// Evaluate and store the result
			moves += result.moves;
			totalMoves += result.moves;
			if (result.winner == 1){
				play1Wins++;
				play1TotalWins++;}
			else if (result.winner == 2){
				play2Wins++;
				play2TotalWins++;}}
		catch (const std::exception e){}

		globals.gamesPlayed++;
	}

#pragma endregion
	// Add totals to end of train_results.txt
	str_allResults << "0 " << globals.episodes - 1 << " " << play1TotalWins << " " << play2TotalWins
		<< " " << play1RandWins << " " << play2RandWins << " " << (totalMoves / globals.episodes) << " " << (totalRandMoves / globals.episodes) << '\n';
	// Print allResults to File
	std::ofstream allResultsOut(globals.allResultsFile + ".txt", std::ofstream::ate);
	allResultsOut << str_allResults.str();
	globals.net1->save(globals.netFile1 + ".net");
	
	return 0;
}