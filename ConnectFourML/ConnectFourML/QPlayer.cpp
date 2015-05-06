

#include "Qplayer.h"

int QPlayer::getMove(){
	// Get 7 next state values
		// uses QLearn obj
		// Send (S, QSA, MaxQSA, r) to QLearn Obj. r is always zero, but will update if win.
	// Choose explore or greedy
	// Loop until valid move picked (greedy -> least greedy)
	// return move
}

void QPlayer::hasWon(){
	// TODO update last QTS entry to change reward to 1
}