#include <iostream>
#include <string>
#include <time.h>
#include "MainHelper.h"
#include "LearnPlayer.h"

//using std::cout;
//using std::vector;
//using std::string;

//Globals globals = Globals();

// Declared in MainHelper.h
vector< vector<char> > place;	
Player* player;
int charsPlaced;

Connect4Result ConnectFour()
{
	std::vector<MoveDepth> gameSequence;// = globals.gameSequence;
	int colChoice;				// Will house user row choice
	int depthChoice = 0;		// Will hold drop value
	charsPlaced = 0;
	bool gamewon = false;

	// fill place with whitespaces //
	place.clear();
	place.resize(6, vector<char>(7, ' '));

	// Neural Nets //
	FANN::neural_net* net1 = globals.net1;
	FANN::neural_net* net2 = globals.net2;

	// Initialize LearnObject //
	Learn learnObj = Learn();
	learnObj.setNet(net1);
	learnObj.setDecay(globals.RL_DECAY);
	learnObj.setLearn(globals.RL_LEARNFACTOR);

	Learn learnObj2 = Learn();
	learnObj2.setNet(net2);
	learnObj2.setDecay(globals.RL_DECAY);
	learnObj2.setLearn(globals.RL_LEARNFACTOR);

	// Initialize two players
	Player* play1;
	Player* play2;

	// Check what type of player Player 1 is
	if (globals.player1Learning){
		play1 = &LearnPlayer(CHAR1, &learnObj);
	}
	else{
		play1 = &RandomPlayer(CHAR1);
	}
	// Check what type of player Player 2 is
	if (globals.player2Learning){
		if (globals.loadNet2){
			play2 = &LearnPlayer(CHAR2, &learnObj2);
		}
		else{
			play2 = &LearnPlayer(CHAR2, &learnObj);
		}
	}
	else{
		play2 = &RandomPlayer(CHAR2);
	}
	
	if (globals.playRandomPlayer)
		play2 = &RandomPlayer(CHAR2);
	
	// Alternate starting Player
	if (globals.gamesPlayed % 2 == 0)
		player = play2;
	else
		player = play1;
	

	// Main game loop
	while (!gamewon && charsPlaced < 42){
		// Swap current player
		if (player->getPiece() == CHAR2)
			player = play1;
		else
			player = play2;

		// Get current player move
		// getMove() must only return legal move
		colChoice = player->getMove();
		// Break if game over
		if (charsPlaced == 42) break;
		depthChoice = drop(colChoice, player->getPiece());
		gamewon = check(depthChoice, colChoice);
		charsPlaced++;
		if (player->getPiece() == CHAR2);
		{
			gameSequence.push_back(MoveDepth(depthChoice, colChoice, player->getPiece()));

		}		//r// system("cls");						//This clears the screen works with windows, not nesscery to run game

		// End of main game loop
	}

	// End of a game
	// Display board if display flag (-d)
	if (globals.showBoard){
		displaySequence(gameSequence);
	}



 	if (globals.isTraining || globals.isCompetition){
	/////////////////// Save every 1/10 while training
		int game_range = globals.episodes / 10;      
		std::stringstream ss;
		ss << "train_gameNum_" << (globals.gamesPlayed + 1) << ".txt";
		std::string gameFileName =  ss.str();
		if (((globals.gamesPlayed + 1) % game_range == 0))
		{
			// Print Game Sequence //
			std::ofstream out(gameFileName, std::ofstream::out);
			auto coutbuf = std::cout.rdbuf(out.rdbuf()); //save and redirect
			std::string sType = typeid(*play1).name();

			if (globals.isTraining && !globals.isCompetition)
			{
				cout << "Game " << globals.gamesPlayed + 1 << "\n";
				cout << "Player1 (x) is " << sType << std::endl;
				sType = typeid(*play2).name();
				cout << "Player2 (o) is " << sType << std::endl;
			}

			if (globals.isCompetition)
			{
				cout << "Game " << globals.gamesPlayed + 1 << "\n";
				cout << "Player1 (x) is " << globals.play1Name << std::endl;
				sType = typeid(*play2).name();
				cout << "Player2 (o) is " << globals.play2Name << std::endl;
			}

			displaySequence(gameSequence);
			out.flush();
			out.close();
			cout.rdbuf(coutbuf);
			
			// Save every 1/10 net //
			std::stringstream ss2;
			ss2 << globals.netFile1 << "_game_"
									<< globals.gamesPlayed + 1 << ".net";
			std::string file = ss2.str();
			net1->save(file);
		}

	
	}

	// Tie
	Connect4Result ret;
	if (charsPlaced == 42){
		//cout << 0 << ',' << charsPlaced << "\n";
		play1->hasTied();
		play2->hasTied();
		ret.winner = 0;
		ret.moves = charsPlaced;
	}
	else{
	// Player 2 Won
		if (player->getPiece() == CHAR2){
			//cout << 2 << ',' << charsPlaced << "\n";
			play2->hasWon();
			play1->hasLost();
			ret.winner = 2;
			ret.moves = charsPlaced;
		}
	// Player 1 won
		else{
			//cout << 1 << ',' << charsPlaced << "\n";
			play1->hasWon();
			play2->hasLost();
			ret.winner = 1;
			ret.moves = charsPlaced;
		}
	}
	// Tell Learn that it can update NN
	play1->endGame();
	play2->endGame();

	return ret;
}
