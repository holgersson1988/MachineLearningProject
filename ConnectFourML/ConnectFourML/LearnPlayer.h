#pragma once

/*
 * Extends the MainHelper::Player interface to interact with the connect four
 * game module. QPlayer utilizes a QLearn object to approximate state Q-values.
 *
 */
#include <iostream>
#include "MainHelper.h"
#include "Learn.h"
using std::cout;
using std::vector;

/*
 * Extends Player. Uses the Learn class to implement reinforcement learning
 * game play.
 */
class LearnPlayer : public Player
{
public:
	Learn LearnObj;

	// default constructor
	LearnPlayer(char tPiece) : Player(tPiece){};
	LearnPlayer(char tPiece, Learn &tLearn) 
		: Player(tPiece)
	{
		LearnObj = tLearn;
	};

	virtual int getMove() override;

	/*
	 * Signal to this player that it has won. Used to update reward QTS tuple.
	 */
	virtual void hasWon() override;
};