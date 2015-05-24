
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

	// Save stats for what opening move we made.
	if (piece == CHAR1)
	{
		globals.p1OpeningMoves[move]++;
	}
	else
	{
		globals.p2OpeningMoves[move]++;
	}
	return move;

}

/*
 * Called by ConnectFour after game is over. 
 */
void LearnPlayer::hasWon(){
	//learnSequence.back().setReward(1);
	learnSequence[learnSequence.size() - 1].setReward(1);
	LearnObj->updateTrainSet(learnSequence);
}

void LearnPlayer::hasLost(){
	//learnSequence.back().setReward(-1);
	learnSequence[learnSequence.size() - 1].setReward(-1);
	LearnObj->updateTrainSet(learnSequence);
}

void LearnPlayer::hasTied(){
	Globals globals;
	learnSequence[learnSequence.size() - 1].setReward(globals.RL_REWARD_TIE);
	//learnSequence.back().setReward(globals.RL_REWARD_TIE);
	LearnObj->updateTrainSet(learnSequence);
}

void LearnPlayer::endGame(){
	LearnObj->endGame();
}