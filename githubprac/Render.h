#pragma once
#include <iostream>
using namespace std;

class Render {
private:
	int** dat;
	int gamemode;
	int size;
	string component[11] = { "┌","┬","┐","├","┼","┤","└","┴","┘","│","─"};
	string stone[2] = { "●","○" };
	void printtop();
	void printline(int row);
	void printcomponent(int row, int i, int k);
	void printlast(int row);

public:
	int alpha, beta;
	void initdata(int** _dat);
	void selectmode(int _gamemode);
	void inputxy(char x, char y);
	void printgame();
	void printwinner(int winner);
};