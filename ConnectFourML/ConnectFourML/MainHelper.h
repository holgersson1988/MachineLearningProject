#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <sstream>
#include "floatfann.h"
#include "fann_cpp.h"

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
	fann_type* state;
	fann_type value;
	int reward;

	LearnTuple(){}

	LearnTuple(fann_type* tState, fann_type tValue, int tReward);

	void setReward(int r) { reward = r; }

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

int ConnectFour(bool showBoard);

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