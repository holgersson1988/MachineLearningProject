#include "MainHelper.h"
#include <string>
#include <ios>
#include <iostream>
#include <iomanip>



int main(int argc, char* argv[])
{
	// parse arguments
	bool showBoard = false;
	for (int i = 0; i < argc; i++){
		if (std::string(argv[i]) == "-d")
			showBoard = true;
	}

#pragma region test trainSetToStringy
	vector<TrainPair> trainSet;
	bool input[84] = { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
	trainSet.push_back(TrainPair(input, 0.98));
	std::string str;
	trainSetToString(trainSet, str);
	std::cout << str;
#pragma endregion
	//ConnectFour();
	system("pause");
	return 0;

}