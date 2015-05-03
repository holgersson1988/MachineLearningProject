#include "MainHelper.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

/*
display()

Prints the game board
*/
void display(){
	cout << " 1   2   3   4   5   6   7\n";
	for (int a = 0; a <= 5; a++)
	{
		for (int b = 0; b <= 6; b++) cout << char(218) << char(196) << char(191) << " ";
		cout << '\n';
		for (int b = 0; b <= 6; b++) cout << char(179) << place[a][b] << char(179) << " ";
		cout << '\n';
		for (int b = 0; b <= 6; b++) cout << char(192) << char(196) << char(217) << " ";
		cout << '\n';
	}
}


bool check(int a, int b){
	int vertical = 1;//(|)
	int horizontal = 1;//(-)
	int diagonal1 = 1;//(\)
	int diagonal2 = 1;//(/)
	char player = place[a][b];
	int i;//vertical
	int ii;//horizontal

	//check for vertical(|)
	for (i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);//Check down
	for (i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);//Check up
	if (vertical >= 4)return true;

	//check for horizontal(-)
	for (ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);//Check left
	for (ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);//Check right
	if (horizontal >= 4) return true;

	//check for diagonal 1 (\)
	for (i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);//up and left
	for (i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);//down and right
	if (diagonal1 >= 4) return true;
	//check for diagonal 2(/)
	for (i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);//up and right
	for (i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);//up and left
	if (diagonal2 >= 4) return true;
	return false;
}

int getMoveDepth(int b)
{
	if (b >= 0 && b <= 6)
	{
		if (place[0][b] == ' ')
		{
			int i;
			for (i = 0; place[i + 1][b] == ' '; i++);
			return i;
		}
		else
		{
			return -1;
		}

	}
	else{
		return -1;
	}
}
int drop(int b, char player){
	int depth;
	if (depth = getMoveDepth(b) >= 0)
	{
		place[depth][b] = player;
		return depth;
	}
	else
	{
		return -1;
	}

}

/*
class Player

Interface class to be extended. When player.getMove() is called, a number
from 0-6 is returned as a choice.
*/
class Player
{
public:
	char piece;
	Player(char piece){
		piece = piece;
	}
	virtual int getMove(char place[6][7]) = 0; // virtual signifies that it can be overidden 
};

class RandomPlayer : Player
{
	int getMove(char place[6][7])
	{
		int column = rand() % 7;				// random column
		int depth = getMoveDepth(column);		// Get depth and validate
		return depth;
	}
};