#include "MainHelper.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

using std::cout;
using std::vector;

/*
 * Prints the game board
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

/*
 * Checks to see if move at location (a,b) created a win.
 */
bool check(int a, int b){
	int vertical = 1;//(|)
	int horizontal = 1;//(-)
	int diagonal1 = 1;//(\)
	int diagonal2 = 1;//(/)
	char tPlace[6][7] = { ' ' };
	int i;//vertical
	int ii;//horizontal

	// vector -> array
	for (int a = 0; a < 6; a++)
	{
		for (int b = 0; b < 7; b++){
			tPlace[a][b] = place[a][b];
		}
	}
	char player = tPlace[a][b];
			

	//check for vertical(|)
	for (i = a + 1; tPlace[i][b] == player && i <= 5; i++, vertical++);//Check down
	for (i = a - 1; tPlace[i][b] == player && i >= 0; i--, vertical++);//Check up
	if (vertical >= 4)return true;

	//check for horizontal(-)
	for (ii = b - 1; tPlace[a][ii] == player && ii >= 0; ii--, horizontal++);//Check left
	for (ii = b + 1; tPlace[a][ii] == player && ii <= 6; ii++, horizontal++);//Check right
	if (horizontal >= 4) return true;

	//check for diagonal 1 (\)
	for (i = a - 1, ii = b - 1; tPlace[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);//up and left
	for (i = a + 1, ii = b + 1; tPlace[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);//down and right
	if (diagonal1 >= 4) return true;
	//check for diagonal 2(/)
	for (i = a - 1, ii = b + 1; tPlace[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);//up and right
	for (i = a + 1, ii = b - 1; tPlace[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);//up and left
	if (diagonal2 >= 4) return true;
	return false;
}

/*
* Returns depth of move choice 'b'. Zero is highest placement
* on board. Returns -1 if move is invalid.
*/
int getMoveDepth(int b)
{
	if (b >= 0 && b <= 6)
	{
		if (place[0][b] == ' ')
		{
			int depth;
			for (int i = 0; i < 6; i++)
			{
				if (place[i][b] == ' ')
					depth = i;
			};
			return depth;
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
	int depth = getMoveDepth(b);
	if (depth >= 0)
	{
		place[depth][b] = player;
		return depth;
	}
	else
	{
		return -1;
	}
	
}

Player::Player(char tPiece = CHAR1){
	piece = tPiece;
}

int RandomPlayer::getMove()
{
	int column;
	int depth = -1;

	// Ensures that a valid move is chosen
	while (depth <= -1)
	{
		column = rand() % 7;				// random column
		depth = getMoveDepth(column);		// Gets depth and validate
	}
	
	return column;
}
