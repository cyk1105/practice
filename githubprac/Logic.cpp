#include "Logic.h"

void Logic::gaindata(int x,int y) {
	for (int i = 0; i < 8; i++) {
		gaindir(i, x, y);
	}
}

void Logic::gaindir(int dir, int x, int y) { // 플레이어가 놓은 돌의 색과 같은 돌의 좌표와 방향을 모두 수집
	x += move[dir][0];
	y += move[dir][1];
	while (x >= 0 && y >= 0 && x < size && y < size) {
		if (dat[x][y] == color) {
			save[cnt].x = x;
			save[cnt].y = y;
			save[cnt].dir = dir;
			cnt++;
		}
		else if (dat[x][y] == EMPTY) break; // 중간에 공백이 있을 경우 수집을 중지하고, 그 이후부터는 기록되지 않습니다.
		x += move[dir][0];
		y += move[dir][1];
	}
}

void Logic::clearsave() { // 다음 턴을 위해 저장해놓은 좌표값과 방향을 모두 초기화
	for (int i = 0; i < cnt; i++) {
		save[i].x = -1;
		save[i].y = -1;
		save[i].dir = -1;
	}
	cnt = 0;
}

void Logic::chcolor() {
	color = 3 - color;
}

int Logic::abs(int a) { // 입력받은 값의 절대값 리턴
	if (a < 0) return -a;
	else return a;
}

void Logic::makedat() {
	dat = (int**)malloc(sizeof(int*) * size);
	dat[0] = (int*)malloc(sizeof(int) * size * size);
	for (int i = 1; i < size; i++)dat[i] = dat[i - 1] + size;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) dat[i][j] = EMPTY;
	}
	if (gamemode == 2) {
		dat[3][3] = dat[4][4] = BLACK;
		dat[3][4] = dat[4][3] = WHITE;
	}
}

void Logic::deletedat() {
	free(dat[0]);
	free(dat);
}

int** Logic::redat() {
	return dat;
}

void Logic::pass() { // 플레이어가 돌을 놓지 않고 상대 턴으로 넘기고 싶을 때 사용, 오델로에서는 연속으로 패스가 2번 발생 시 종료
	ps++;
}

void Logic::chmode(int _gamemode) {
	gamemode = _gamemode;
	if (gamemode == 1) size = 16;
	else size = 8;
}

void Logic::setdat(int x, int y) {
	if (x != -1 || y != -1) {
		if (dat[x][y] == EMPTY) {
			ps = 0;
			dat[x][y] = color;
			gaindata(x, y);
		}
		else {
			pass();
			chcolor();
		}
	}
}

int Logic::Omokwinner(int x, int y) {
	int dirstone[8] = { 0,0,0,0,0,0,0,0 }; // 8방향으로 놓은 돌과 연속된 위치에 있는 같은 색의 돌 탐색 후 저장
	int _dir = 0;
	for (int i = 0; i < cnt; i++) {
		if (save[i].dir == _dir) {
			if (dirstone[_dir] == 0) {
				if (abs(save[i].x - x) <= 1 && abs(save[i].y - y) <= 1)
					dirstone[_dir]++;
				else _dir++;
			}
			else {
				if (abs(save[i].x - save[i - 1].x) <= 1 && abs(save[i].y - save[i - 1].y) <= 1)
					dirstone[_dir]++;
				else _dir++;
			}
		}
		else {
			if (save[i].dir > _dir) { _dir++; i--; }
		}
	}
	for (int i = 0; i < 4; i++) {
		if (dirstone[i] + dirstone[7 - i] >= 4) return color;
	}
	clearsave();
	chcolor();
	return 0;
}

int Logic::Othellowinner(int x, int y) {
	if (ps > 0 && ps < 2) {
		chcolor();
		return 0;
	}
	int a = x;
	int b = y;
	int dirstone[8] = { -1,-1,-1,-1,-1,-1,-1,-1 }; // 플레이어가 놓은 돌을 기준으로 8방향에서 처음에 놓인 돌의 위치(save의 번호)만 저장
	int _dir = 0;
	int count = 0;
	for (int i = 0; i < cnt; i++) {
		if (save[i].dir == _dir) {
			dirstone[_dir] = i;
			_dir++;
		}
		else {
			if (save[i].dir > _dir) { _dir++; i--; };
		}
	}
	int moveX, moveY;
	for (int i = 0; i < 8; i++) {
		if (dirstone[i] == -1) continue;
		int k = dirstone[i];
		if (save[k].x - x == 0)moveX = 0;
		else moveX = (save[k].x - x) / abs(save[k].x - x);
		if (save[k].y - y == 0)moveY = 0;
		else moveY = (save[k].y - y) / abs(save[k].y - y);
		a = a + moveX;
		b = b + moveY;
		while (dat[a][b] != color) {
			dat[a][b] = color;
			cntstone[color - 1]++;
			cntstone[2 - color]--;
			a = a + moveX;
			b = b + moveY;
			count++;
		}
		a = x;
		b = y;
	}
	clearsave();
	if (count == 0) dat[x][y] = 0;
	else chcolor();
	if (ps == 2 || cntstone[WHITE - 1] + cntstone[BLACK - 1] == size * size) {
		if (cntstone[WHITE - 1] > cntstone[BLACK - 1]) return 1;
		else if (cntstone[WHITE - 1] < cntstone[BLACK - 1]) return 2;
		else return 3;
	}
	return 0;
}