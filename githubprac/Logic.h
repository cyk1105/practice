#pragma once
#include <iostream>
#define EMPTY 0
#define WHITE 1
#define BLACK 2
using namespace std;

class Logic {
private:
	int** dat;
	int size, gamemode;
	int color = WHITE;
	int cnt = 0;
	int ps = 0;
	int cntstone[2] = { 2,2 };
	int move[8][2] = { {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };
	struct { int x = -1; int y = -1; int dir = -1; }save[100]; // 같은 색의 돌의 좌표를 저장할 목적
	void gaindata(int x, int y);
	void gaindir(int dir, int x, int y);
	void clearsave();
	void chcolor();
	int abs(int a);

public:
	void makedat();
	void deletedat();
	int** redat();
	void pass();
	void chmode(int _gamemode);
	void setdat(int _alpha, int _beta);
	int Omokwinner(int x, int y);
	int Othellowinner(int x, int y);
};