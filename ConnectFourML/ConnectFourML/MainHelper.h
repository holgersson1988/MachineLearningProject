#pragma once

#define PLAY2	15
#define PLAY1	254

class MainHelper
{
public:
	MainHelper();
	~MainHelper();

	void display();
	bool check(int a, int b);
	int drop(int b, char player);
};

