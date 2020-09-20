#include <bangtal.h>
#include <iostream>
#include <string>

using namespace bangtal;
using namespace std;

int map[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
int bx = 2, by = 2;		//빈 칸의 위치 x행, y열

class Piece {
public:
	int centerX, centerY;
	ObjectPtr piece;
	string path;
	Piece(string loc, ScenePtr scene, int cx, int cy) : path(loc), centerX(cx), centerY(cy) {
		piece = Object::create(path, scene, centerX, centerY, true);
	}
};


//전달받은 횟수만큼 퍼즐판을 초기화 하는 함수
void shuffle(int n) {
	int random[4][2] = { {0,-1},{0,1},{1,0},{-1,0} };
	for (int i = 0;i < n; ) {
		move(bx + random[rand() % 4][0], by + random[rand() % 4][1]);
	}
}

//전달받은 키값으로 퍼즐을 이동시키는 함수
void move( int cx, int cy) {

	//배열 밖에서의 이동을 방지
	if (cy == -1 || cy == 3)
		return;
	if (cx == -1 || cx == 3)
		return;

	if (bx + 1 == cy) {
		map[bx][by] = map[bx + 1][by];
		map[++bx][by] = 0;
	}
	case down:
		map[bx][by] = map[bx - 1][by];
		map[--bx][by] = 0;
		break;
	case left:
		map[bx][by] = map[bx][by + 1];
		map[bx][++by] = 0;
		break;
	case right:
		map[bx][by] = map[bx][by - 1];
		map[bx][--by] = 0;
		break;
	default:
		return;
	}
	++nMove;
}

//퍼즐 게임이 끝났는지 확인하는 함수, 끝이면 true를 아니면 false를 반환합니다.

bool isDone() {
	int n = 1, x, y;
	for (x = 0; x < 3; ++x) {
		for (y = 0; y < 3; ++y) {
			if (x == 2 && y == 2)	//map[2][1]까지 완성된 것이 확인됐을 경우
				return true;
			else if (n != map[x][y])
				return false;
			++n;
		}
	}
}


int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	auto scene = Scene::create("퍼즐", "Images/원본.png");


	Piece pieces[9] = {
		Piece("Images/1.jpg",scene,0,0), Piece("Images/2.jpg",scene,0,0), Piece("Images/3.jpg",scene,0,0),
		Piece("Images/4.jpg",scene,0,0), Piece("Images/5.jpg",scene,0,0), Piece("Images/6.jpg",scene,0,0),
		Piece("Images/7.jpg",scene,0,0), Piece("Images/8.jpg",scene,0,0), Piece("Images/9.jpg",scene,0,0) };

	//퍼즐 판 배열

	int cx, cy; // 클릭된 위치 x행, y열 
	int nMove =0 ;	//이동 횟수

	auto timer = Timer::create(180.f);
	showTimer(timer);

	ObjectPtr startButton = Object::create("Images/start.png", scene, 590, 70);
	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool s{

		// start game
		startButton->hide();
		scene->setImage("Images/배경.jpg");
		timer->set(180.f);
		timer->start();
		shuffle(30);
		return true;
});

	for (int i = 0; i < 9; i++) {
		pieces[i].piece->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			if (isDone()) {
				timer->stop();
				showMessage("게임 성공");
				endGame();
			}
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++)
					if (map[x][y] == i) {
						cx = x;
						cy = y;
					}
				move( cx, cy);
				return true;
			}});
	}
	timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		showMessage("게임 종료");
		return true;
		});

	startGame(scene);
	return 0;
}