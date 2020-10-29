#include <bangtal>
#include <iostream>
#include <time.h>
#include "Board.h"

using namespace bangtal;
using namespace std;

ScenePtr scene = nullptr;


int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	srand((unsigned int)time(NULL));


	// 원래 방탈출라이브러리 1280 x 720 
	scene = Scene::create("뽀로로", "images/배경.jpg");

	// 오브젝트 1 시간 설정
	time_t start_time; // 시작 시간 설정
	auto counttimer = Timer::create(30.f); // 문제 풀이 시간 

	// 오브젝트 2 게임 버튼
	auto startButton = Object::create("Images/start.png", scene, 590, 70);
	auto endButton = Object::create("Images/end.png", scene, 590, 20);
	showTimer(counttimer);

	// while문을 대체하는 타이머
	auto count = 0;
	auto timer = Timer::create(0.1f);

	//보드 
	Board::getInst()->init(scene);
	for (int i = 0; i < 9; i++) {
		// 각 오브젝트마다 모두 콜백 함수 정의 
		Board::getInst()->getObject(i)->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)->bool {
		int j = 0;

		// 클릭된 오브젝트를 콜백이 받아오면, 보드판의 오브젝트와 주소 비교 
		for (j = 0; j < 9; j++)
		{
			if (Board::getInst()->getObject(j) == object) break;
		}

		// 클릭된 오브젝트 근처에 블랭크 확인
		if (Board::getInst()->check(j)) {
			// 위치 변경 - 블랭크 위치로 <-> 블랭크는 해당 도형 위치로 변경
			Board::getInst()->swap(j);
		
		}
		//변경하고 나서 -> 다 맞췄는지 확인하기 
		if(Board::getInst()->compare())
		{	auto end_time = time(NULL);
				startButton->setImage("Images/restart.png");
				startButton->show();
				endButton->show();
				timer->stop();// 타이머 스탑해주기 
				string buf = "성공! " + to_string(difftime(end_time, start_time)) + "초 걸렸습니다";
					//showMessage 는 char* 타입만 받음 
				showMessage(buf.c_str());
		}
		return true;
	});
	}

	//start game -> 마우스 콜백 사용 
	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		startButton->hide();
		endButton->hide();

		counttimer->start();
		start_time = time(NULL); // 현재 시간 알아옴

		// blank만 하얗게 처리 
		Board::getInst()->getObject(8)->hide();
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



	// while 문을 대체 타이머가 종료되면 호출되는 콜백 
	timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		int j = 0;
		int blank = Board::getInst()->getBlank();
		//블랭크 위치를 뭘로 변경할지 선택
		
		do {
			switch (rand() % 4) {
			case 0: j = blank - 1; break;
			case 1: j = blank + 1; break;
			case 2: j = blank - 3; break;
			case 3: j = blank + 3; break;
			}
		}
		//해당 예외처리 넘기기
		while (j < 0 || j > 8 || !Board::getInst()->check(j));
		Board::getInst()->swap(j);

		// 5번만 재시작하기 위해서
		count++;
		// 반복을 위해서 콜백함수안에서 다시 호출해줘야함
		if (count < 5) {
			timer->set(0.1f);
			timer->start();
		}
		return true;
	});
	
	startGame(scene);
}