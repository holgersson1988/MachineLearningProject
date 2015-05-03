#pragma once

#define CHAR2	char(15)
#define CHAR1	char(254)

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

	virtual int getMove()= 0; // virtual signifies that it can be overidden 
	char getPiece(){ return piece; };
};

class RandomPlayer : public Player
{
	public:

		// default constructor
		RandomPlayer(char piece)
			: Player(piece){};
		/*
		Returns random choice from 0-6.
		*/
		int getMove() override;
};
