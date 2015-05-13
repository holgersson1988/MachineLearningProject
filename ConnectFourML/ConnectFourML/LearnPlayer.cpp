
#include "LearnPlayer.h"

/*
 * Return a valid move. Calls Learn.nextState() to return a greedy or
 * exploratory choice.
 */
int LearnPlayer::getMove() {
	int move = LearnObj.nextState();
	return move;
}

/*
 * Called by ConnectFour after game is over. Calls Learn.hasWon().
 */
void LearnPlayer::hasWon(){
	LearnObj.hasWon();
}
