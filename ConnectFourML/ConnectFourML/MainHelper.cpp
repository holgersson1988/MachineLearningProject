#pragma once
#include "MainHelper.h"

using std::cout;
using std::vector;

LearnTuple::LearnTuple(bool* tState, float tValue, int tReward){
	state = tState;
	value = tValue;
	reward = tReward;
}

MoveDepth::MoveDepth(int tDepth, int tMove, char tPlayer){
	move = tMove;
	depth = tDepth;
	player = tPlayer;
}

Player::Player(char tPiece){
	piece = tPiece;
}

/*
* Returns a valid random move as an int
*/
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


void displaySequence(vector<MoveDepth> sequence){
	vector<vector<char>> board(6, vector<char>(7, ' '));
	for (vector<MoveDepth>::iterator it = sequence.begin(); it != sequence.end(); ++it){
		int depth = it->depth;
		int move = it->move;
		char player = it->player;
		board[depth][move] = player;
		display(board, depth, move);
	}
}


void display(vector<vector<char>> board, int depth, int move){
	cout << " 1   2   3   4   5   6   7\n";
	for (int a = 0; a <= 5; a++)
	{
		for (int b = 0; b <= 6; b++){
			if (a != depth || b != move)
				cout << char(218) << char(196) << char(191) << " ";
			else
				cout << "*" << char(196) << "*" << " ";
		}
		cout << '\n';
		for (int b = 0; b <= 6; b++){
				cout << char(179) << board[a][b] << char(179) << " ";
		}
		cout << '\n';
		for (int b = 0; b <= 6; b++){
			if (a != depth || b != move)
				cout << char(192) << char(196) << char(217) << " ";
			else
				cout << "*" << char(196) << "*" << " ";
		}
		cout << '\n';
	}
	cout << std::endl;
}

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


