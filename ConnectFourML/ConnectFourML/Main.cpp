#include "MainHelper.h"
#include <string>
#include <ios>
#include <iostream>
#include <iomanip>

// Forward Dec. Remove.
void testFANN();
void xor_test();

int main2(int argc, char* argv[])
{
	// parse arguments
	bool showBoard = false;
	for (int i = 0; i < argc; i++){
		if (std::string(argv[i]) == "-d")
			showBoard = true;
	}

	//ConnectFour(showBoard);
	//testFANN();
	/*
	try
	{
		std::ios::sync_with_stdio(); // Syncronize cout and printf output
		xor_test();
	}
	catch (...)
	{
		std::cerr << std::endl << "Abnormal exception." << std::endl;
	}
	system("pause");*/
	return 0;

}