#pragma once
#include "QLearn.h"
#include "MainHelper.h"


float Learn::getValue(char* tState[7]){

}

/*
Returns a bitstring to use as input for the ANN from the gameState array in Connect 4
*/
bool* QLearn::getInput(char** gameState)
{
	bool* ret = new bool[84];

	for (int i = 0; i < 6; i++)
	{
		for (int ii = 0; ii < 7; ii++)
		{
			char val = gameState[i][ii];
			int returnIndex = i*ii;
			// Check for player 1
			if ((i*ii) % 2 == 0)
			{
				if (val == CHAR1)
				{
					ret[returnIndex] = true;
				}
				else
				{
					ret[returnIndex] == false;
				}
			}
			// Check for player 2 char
			else
			{
				if (val == CHAR2)
				{
					ret[returnIndex] = true;
				}
				else
				{
					ret[returnIndex] == false;
				}
			}
		}
	}
	return ret;
}