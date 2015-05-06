#pragma once

/*
 * Extends the MainHelper::Player interface to interact with the connect four
 * game module. QPlayer utilizes a QLearn object to approximate state Q-values.
 *
 */
#include "MainHelper.h"
#include "QLearn.h"

class QPlayer : Player
{
public:
	QLearn QLearnObj;

	// default constructor
	QPlayer(char tPiece, QLearn &tQLearn) 
		: Player(tPiece)
	{
		QLearnObj = tQLearn;
	};

	int getMove() override;

	/*
	Signal to this player that it has won. Used to update reward of last
	saved QTS tuple.
	*/
	void hasWon();
};