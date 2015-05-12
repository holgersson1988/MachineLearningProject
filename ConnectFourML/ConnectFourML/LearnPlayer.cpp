
#include "LearnPlayer.h"
#include "Learn.h"

/*
 * Return a valid move. Calls Learn.nextState() to return a greedy or
 * exploratory choice.
 */
int LearnPlayer::getMove() {
	//int move = LearnObj.nextState(); // <
	//return move;
	return 0;
}

/*
 * Called by ConnectFour after game is over. Updates last value of
 * Learn.learnTrainSequence to update reward = 1. May be that only
 * a general 'game over' function is needed to update both reward
 * and function.
 */
void LearnPlayer::hasWon(){
	// TODO update last QTS entry to change reward to 1
}

void LearnPlayer::hasLost(){
	// TODO
}