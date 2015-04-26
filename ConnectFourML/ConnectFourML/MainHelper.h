#pragma once
class MainHelper
{
public:
	MainHelper();
	~MainHelper();

	void display();
	bool check(int a, int b);
	int drop(int b, char player);
	char place[6][7];//available for whole program
};

