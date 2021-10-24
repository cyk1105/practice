#include "Render.h"

void Render::printtop() {
	if (gamemode == 1) cout << " 0 1 2 3 4 5 6 7 8 9 a b c d e f" << '\n';
	else cout << "   0   1   2   3   4   5   6   7" << '\n';
}

void Render::printline(int row) {
	if (gamemode == 2) { // 오델로의 경우 '칸'의 형식으로 출력해야 하기 때문에 위에 덮을 칸 한 줄을 추가
		for (int i = 0; i < size + 1; i++) {
			printcomponent(row, i, 2);
			if (i < size)cout << component[10];
		}
		cout << '\n';
	}
	for (int i = 0; i < size; i++) {
		if (gamemode == 2) cout << component[9];
		printcomponent(row, i, 1);
	}
	printlast(row);
}

void Render::printcomponent(int row, int i, int k) {
	int m, n;
	if (gamemode == 1) n = size;
	else n = size + 1;
	if (row == 0) {
		if (i == 0) m = 0;
		else if (i == n - 1) m = 2;
		else m = 1;
	}
	else if (row == n - 1) {
		if (i == 0) m = 6;
		else if (i == n - 1) m = 8;
		else m = 7;
	}
	else {
		if (i == 0) m = 3;
		else if (i == n - 1) m = 5;
		else m = 4;
	}
	if (k == 2) cout << component[m]; // 오델로용 덮는 칸 출력
	else {
		if (dat[row][i] == 0) {
			if (gamemode == 1) cout << component[m];
			else cout << "  ";
		}
		else {
			int t = dat[row][i];
			cout << stone[t - 1];
		}
	}
}

void Render::printlast(int row) {
	if (gamemode == 2) cout << component[9] << " " << row;
	else {
		if (row < 10) cout << " " << row;
		else cout << " " << char('a' + row - 10);
	}
}

void Render::initdata(int** _dat) {
	dat = _dat;
}

void Render::selectmode(int _gamemode) {
	gamemode = _gamemode;
	if (gamemode == 1) size = 16;
	else size = 8;
}

void Render::inputxy(char x, char y) {
	if ('a' <= x && x <= 'f') alpha = x - 'a' + 10;
	else alpha = x - '0';
	if ('a' <= y && y <= 'f') beta = y - 'a' + 10;
	else beta = y - '0';
}

void Render::printgame() {
	system("cls");
	printtop();
	for (int i = 0; i < size; i++) {
		printline(i);
		cout << '\n';
	}
	if (gamemode == 2) { // 오델로의 경우 맨 아래 덮는 라인 추가 
		for (int i = 0; i < size + 1; i++) {
			printcomponent(size, i, 2);
			if (i < size)cout << component[10];
		}
		cout << '\n';
	}
	cout << "Input data: ";
}

void Render::printwinner(int winner) {
	if (winner == 1) cout << "White Win!!!";
	else if (winner == 2) cout << "Black Win!!!";
	else cout << "Draw";
}