
#include "LearnPlayer.h"

//Globals globals = Globals();

/*
 * Return a valid move. Calls Learn.nextState() to return a greedy or
 * exploratory choice.
 */
int LearnPlayer::getMove() {
	int move;
	LearnTuple stateInfo = LearnObj->nextState(move);
	learnSequence.push_back(stateInfo);
	return move;

}

/*
 * Called by ConnectFour after game is over. 
 */
void LearnPlayer::hasWon(){
	learnSequence.back().setReward(1);
	LearnObj->updateTrainSet(learnSequence);
}

void LearnPlayer::hasLost(){
	learnSequence.back().setReward(-1);
	LearnObj->updateTrainSet(learnSequence);
}

void LearnPlayer::hasTied(){
	Globals globals;
	learnSequence.back().setReward(globals.RL_REWARD_TIE);
	LearnObj->updateTrainSet(learnSequence);
}

void LearnPlayer::endGame(){
	LearnObj->endGame();
}
