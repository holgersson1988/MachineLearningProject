
#include "LearnPlayer.h"

/*
 * Return a valid move. Calls Learn.nextState() to return a greedy or
 * exploratory choice.
 */
int LearnPlayer::getMove() {
<<<<<<< HEAD
	int move;
	LearnTuple stateInfo = LearnObj.nextState(move);
	learnSequence.push_back(stateInfo);
	return move;
	
=======
	int move = LearnObj.nextState();
	return move;
>>>>>>> origin/ANN-Test
}

/*
 * Called by ConnectFour after game is over. Calls Learn.hasWon().
 */
void LearnPlayer::hasWon(){
	learnSequence.back().setReward(1);
	LearnObj.updateTrainSet(learnSequence);
}

void LearnPlayer::hasLost(){
	learnSequence.back().setReward(-1);
	LearnObj.updateTrainSet(learnSequence);
}
