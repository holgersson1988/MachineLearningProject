#pragma once

#define CHAR2	15 //char(15)
#define CHAR1	43 //char(254)

void display();

/*
Checks to see if move at location (a,b) created a win.
*/
bool check(int a, int b);

/*
Puts 'player' piece in column b if valid move. Returns -1 if error,
positive integer otherwise.
*/
int drop(int b, char player);

extern char place[6][7];

/*
Interface class to be extended. When player.getMove() is called, a number
from 0 - 6 is returned as a choice.
*/
class Player
{
public:
	char piece;

	// default constructor
	Player(char piece);
	/*
	Must return ONLY VALID move.
	*/
	virtual int getMove() = 0; // virtual signifies that it can be overidden 
	virtual void hasWon() = 0;
	char getPiece(){ return piece; };
};

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
};
