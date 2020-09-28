#include <bangtal.h>
#include <iostream>
#include <ctime>

using namespace bangtal;
using namespace std;

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	srand((unsigned int)time(NULL));

	auto scene = Scene::create("뽀로로", "images/배경.jpg");
	ObjectPtr game_board[9];
	ObjectPtr init_board[9];
	int blank = 8;

	// 시간 설정
	time_t start_time;
	auto counttimer = Timer::create(30.f); // 문제 풀이 시간 

	// 게임 버튼
	auto startButton = Object::create("Images/start.png", scene, 590, 70);
	auto endButton = Object::create("Images/end.png", scene, 590, 20);
	showTimer(counttimer);

	//random 생성을 위한 타이머
	auto count = 0;
	auto timer = Timer::create(0.1f);
	
	// start game
	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		startButton->hide();
		endButton->hide();
		counttimer->start();
		start_time = time(NULL); // 현재 시간 알아옴
		game_board[blank]->hide();
		timer->start();
		return true;
	});

	// end Game
	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});

	// time over
	counttimer->setOnTimerCallback([&](TimerPtr timer)->bool {
		startButton->setImage("Images/restart.png");
		startButton->show();
		endButton->show();
		showMessage("Time Over!!!");
		return true;
	});


	for (int i = 0; i < 9; i++) {
		game_board[i] = Object::create("Images/" + to_string(i + 1) + ".jpg", scene, 188 + (i % 3) * 302, 435 -(i/3)*150);
		init_board[i] = game_board[i];
		game_board[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)->bool{
			int j = 0;
			for (j = 0; j < 9; j++) {
				if (game_board[j] == object) break;}

			if ((j % 3 > 0 && j - 1 == blank) ||
				(j % 3 < 3 && j + 1 == blank) ||
				(j > 2 && j - 3 == blank) ||
				(j < 7 && j + 3 == blank)
				) {
				game_board[j]->locate(scene, 188 + (blank % 3) * 302, 435 - (blank / 3) * 150);
				game_board[blank]->locate(scene, 188 + (j % 3) * 302, 435 - (j / 3) * 150);
				game_board[j] = game_board[blank];
				game_board[blank] = object;
				blank = j;
			}
	
			for (int k = 0; k < 9; k++) {
				if (game_board[k] != init_board[k]) break;
				if (k == 8) {
					auto end_time = time(NULL);
					startButton->setImage("Images/restart.png");
					startButton->show();
					endButton->show();
					timer->stop();
					string buf = "성공! "+ to_string(difftime(end_time, start_time)) + "초 걸렸습니다";
					showMessage(buf.c_str());
				}
			}
			return true;

		});
	}
	

	timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		int j = 0;
		do {
			switch (rand() % 4) {
			case 0: j = blank - 1; break;
			case 1: j = blank + 1; break;
			case 2: j = blank - 3; break;
			case 3: j = blank + 3; break;
			}
		}
		while ((j < 0 || j > 8 || !((j % 3 > 0 && j - 1 == blank) ||
				(j % 3 < 3 && j + 1 == blank) ||
				(j > 2 && j - 3 == blank) ||
				(j < 7 && j + 3 == blank))));

			game_board[j]->locate(scene, 188 + (blank % 3) * 302, 435 - (blank / 3) * 150);
			game_board[blank]->locate(scene, 188 + (j % 3) * 302, 435 - (j / 3) * 150);
			auto object = game_board[j];
			game_board[j] = game_board[blank];
			game_board[blank] = object;
			blank = j;
			count++;

			if (count < 5) {
				timer->set(0.1f);
				timer->start();
			}
			return true;
	});
	
	startGame(scene);
}