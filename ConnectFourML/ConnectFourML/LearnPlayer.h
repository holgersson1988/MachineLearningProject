#pragma once

/*
 * Extends the MainHelper::Player interface to interact with the connect four
 * game module. QPlayer utilizes a QLearn object to approximate state Q-values.
 *
 */
#include "MainHelper.h"
#include "Learn.h"

class LearnPlayer : Player
{
public:
	Learn LearnObj;

	// default constructor
	LearnPlayer(char tPiece, Learn &tLearn) 
		: Player(tPiece)
	{
		LearnObj = tLearn;
	};

	int getMove() override;

	/*
	Signal to this player that it has won. Used to update reward QTS tuple.
	*/
	void hasWon() override;

	/*
	Signal to this player that it has lost. Used to update reward of QTS tuple.
	*/
	void hasLost() override;
};