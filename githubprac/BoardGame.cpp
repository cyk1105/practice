#include <iostream>
#include "Logic.h"
#include "Render.h"
using namespace std;

Logic logic;
Render render;

int main(){
	int gamemode;
	char x, y;
	cout << "Input gamemode: ";
	cin >> gamemode;
	logic.chmode(gamemode);
	render.selectmode(gamemode);
	logic.makedat();
	render.initdata(logic.redat());
	render.printgame();
	while (1) {
		cin >> x >> y;
		if (x == 'x' && y == 'x') break;
		if (x == 'p' && y == 's') { 
			logic.pass();
			logic.setdat(-1, -1);
		}
		else {
			render.inputxy(x, y);
			logic.setdat(render.alpha, render.beta);
		}
		if (gamemode == 1) { //오목, 오델로의 경우에 따라서 승부 결과를 다르게 진행
			int k = logic.Omokwinner(render.alpha, render.beta);
			render.printgame();
			if (k != 0) {
				render.printwinner(k);
				break;
			}
		}
		else {
			int k = logic.Othellowinner(render.alpha, render.beta);
			render.printgame();
			if (k != 0) {
				render.printwinner(k);
				break;
			}
		}
	}
	logic.deletedat();
}