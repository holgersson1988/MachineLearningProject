

#include "LearnPlayer.h"

int LearnPlayer::getMove(){
	int stateValue[7];
	LearnObj.getValue(stateValue); // <
	// Get 7 next state values
		// uses QLearn obj
		// Send (S, QSA, MaxQSA, r) to QLearn Obj. r is always zero, but will update if win.
	// Choose explore or greedy
	// Loop until valid move picked (greedy -> least greedy)
	// return move
}

void LearnPlayer::hasWon(){
	// TODO update last QTS entry to change reward to 1
}

void LearnPlayer::hasLost(){

}