#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include <exception>
#include <stdexcept>
#include "floatfann.h"
#include "fann_cpp.h"
#include <cstdlib>
#include "ANN.h"

#define CHAR2	15 //char(15)
#define CHAR1	43 //char(254)
using std::cout;
using std::vector;

/*
	* Saves State, Value, and Reward tuples for generating a training sequence
	* for the neural net.
	*/
struct LearnTuple
{
	vector<fann_type> state;
	fann_type value;
	int reward;

	LearnTuple(){
		reward = 0;
		value = -2;
		state.resize(84, 0.0);
	}

	LearnTuple(vector<fann_type> tState, fann_type tValue, int tReward);

	vector<fann_type> getState(){ return state; }
	fann_type getValue(){ return value; }

	void setReward(int r) { reward = r; }
	void setState(vector<fann_type> tState){ state = tState; }
	void setValue(fann_type tValue){ value = tValue; }
};

/*
* Used to keep a sequence of board game states for printing.
*/
struct MoveDepth
{
public:
	int move;
	int depth;
	char player;

	MoveDepth(int tDepth, int tMove, char tPlayer);

	void setMove(int tMove) { move = tMove; }
	void setDepth(int tDepth) { depth = tDepth; }
	void setPlayer(char tPlayer) { player = tPlayer; }
};

/*


	*/
struct Connect4Result
{
	int winner;
	int moves;
};

/*
	* Interface class to be extended. When player->getMove() is called, a number
	* from 0 - 6 is returned as a choice.
	*/
class Player
{
public:
	char piece;

	Player(char tPiece = CHAR1);

	/*
	* Returns interger range 0-7.
	*/
	virtual int getMove() = 0; // virtual signifies that it can be overidden 
	virtual void hasWon() = 0;
	virtual void hasLost() = 0;
	virtual void hasTied() = 0;
	virtual void endGame() = 0;
	char getPiece(){ return piece; };
};

/*
	* Extends Player class. Makes random moves.
	*/
class RandomPlayer : public Player
{
public:

	// default constructor
	RandomPlayer(char tPiece)
		: Player(tPiece){};
	/*
	Returns random choice from 0-6.
	*/
	int getMove() override;
	void hasWon() override {};
	void hasLost() override {};
	void hasTied() override {};
	void endGame() override {};
};

/*
 * Prints the game board from global variable 'place'
 */
void display();

/*
 * Prints sequence of game boards
 */
void displaySequence(vector<MoveDepth> sequence);

/*
 * Prints single game board
 */
void display(vector<vector<char>> board, int depth, int move);

/*
 * Returns depth of move choice 'b'. Zero is highest placement
 * on board. Returns -1 if move is invalid.
 */
int getMoveDepth(int b);

/*
 * Check to see if position 'a', 'b' caused a win.
 */
bool check(int a, int b);


/*
Puts 'player' piece in column b if valid move. Returns -1 if error,
positive integer otherwise.
*/
int drop(int b, char player);

Connect4Result ConnectFour();

/*
 * Global. Saves state of board.
 */
extern vector< vector<char> > place;
/*
 * Global. Saves current player.
 */
extern Player *player;
/*
 * Global. Saves number of characters placed on board.
 */
extern int charsPlaced;

struct Globals{
public:

	// File Names //
	std::string netFile1 = "train_net1",	// Save net1, is default for one LearnPlayer
		netFile2 = "train_net2",			// Save net2
		resultsFile = "train_results",		// TrainStart TrainEnd WinPlay1 WinPlay2 WinPlay1Rand WinPlay2Rand
		randPlayFile = "train_randPlay",	// 0 99 450 550 677 223
		allResultsFile = "train_allResults"; 

	// Neural Network //
	unsigned int NN_LAYERS = 3,
		NN_INPUTS = 84,
		NN_HIDDEN_NODES = 80,
		NN_OUPUTS = 1,
		NN_MAXEPOCHS = 1000,
		NN_REPORTEVERY = 1001;
	float NN_LEARNRATE = 0.5f,
		NN_LEARNRATE_DECAY = 1.0,
		NN_DESIREDERROR = 0.001;
	bool NN_LEARNRATE_DECAY_BOOL = false;

	// RL Learning //
	float RL_REWARD_TIE = -1.0f,
		RL_EXPLORATION = 0.7f,
		RL_DECAY = 0.97f,
		RL_LEARNFACTOR = 0.5f;

	// Training //
	unsigned int episodes = 100;      // For results set at 50000
	unsigned int randPlayAmount = 10; // For results set at 1000

	// Stats
	int p1OpeningMoves[7]; // = { 0, 0, 0, 0, 0, 0, 0 };
	int p2OpeningMoves[7]; // = { 0, 0, 0, 0, 0, 0, 0 };

	// Other //
	bool isTraining = true,
		showBoard = false,
		playRandomPlayer = false;	// Dont't set to true here
	FANN::neural_net* net1;			// = new FANN::neural_net(); // Create two nets
	FANN::neural_net* net2;			//
	bool player1Learning = true;	// Set if learning or random
	bool player2Learning = true;	//
	bool loadNet1 = false;			// Load net 1 from file?
	bool loadNet2 = false;			// Load net 2 from file? Otherwise it does not exist.
	int gamesPlayed = 0;


Globals()
	{
		// Create net 1
		ANN ArtificialNeuralNet = ANN(NN_LAYERS, NN_INPUTS, NN_HIDDEN_NODES,
			NN_OUPUTS, NN_LEARNRATE);
		net1 = ArtificialNeuralNet.getANN();

		if (loadNet1)
		{
			net1->create_from_file(netFile1 + ".net");
		}
		if (loadNet2)
		{
			net2->create_from_file(netFile2 + ".net");
		}

		for (int i = 0; i < 7; i++)
		{
			p1OpeningMoves[i] = 0;
			p2OpeningMoves[i] = 0;
		}
	}
};
extern Globals globals;
