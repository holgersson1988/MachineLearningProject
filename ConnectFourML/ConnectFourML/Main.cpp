#include "MainHelper.h"
#include <string>

int main(int argc, char* argv[])
{
	// parse arguments
	bool showBoard = false;
	for (int i = 0; i < argc; i++){
		if (std::string(argv[i]) == "-d")
			showBoard = true;
	}

	ConnectFour(showBoard);
}