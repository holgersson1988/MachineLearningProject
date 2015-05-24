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

Connect4Result ConnectFour(FANN::neural_net* net);

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
	// Neural Network //
	unsigned int NN_LAYERS = 3,
		NN_INPUTS = 84,
		NN_HIDDEN_NODES = 250,
		NN_OUPUTS = 1,
		NN_MAXEPOCHS = 1000,
		NN_REPORTEVERY = 1001;
	float NN_LEARNRATE = 0.5f,
		NN_DESIREDERROR = 0.001;

	// RL Learning //
	float RL_REWARD_TIE = -1,
		RL_EXPLORATION = 0.7,
		RL_DECAY = 0.97,
		RL_LEARNFACTOR = 0.5;

	// Training //
	unsigned int episodes = 1000;

	// Other //
	bool isTraining = true,
		showBoard = false,
		saveBoard = true;
	std::vector<MoveDepth> gameSequence;
	int gamesPlayed = 0;
	std::string netLoadFile = "train_net",
		resultSaveFile = "train_results";

};
extern Globals globals;
