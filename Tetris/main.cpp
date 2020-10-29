#pragma once

#include "value.h"
#include "macro.h"
#include <windows.h>
#include <bangtal>
#include "StageManager.h"
#include "ShapeManager.h"
#include <time.h>
using namespace bangtal;


int main(void)
{
	ScenePtr m_scene;
	time_t m_startTime;
	TimerPtr m_countTimer;
	TimerPtr m_repeatTimer;

	HANDLE m_hConsole;

	//1. 필요한 객체 생성 및 초기화
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	srand((unsigned int)time(NULL));
	srand(time(0));

	
	// ** 화면 생성
	m_scene = Scene::create("테트리스", "picture/scene.png");
	auto nextButton = Object::create("picture/nextButton.png", m_scene, 790, 370);

	
	// 스테이지 관리자를 생성 및 초기화한다.
	if (!CStageManager::GenInst()->Init(m_scene)) return 0;



	//while 문을 대신할 타이머
	m_repeatTimer = Timer::create(0.6f);


	
	// start game + end game
	auto startButton = Object::create("picture/start.png", m_scene, 800, 250);
	auto endButton = Object::create("picture/end.png", m_scene, 800, 300);



	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool 
	{

	startButton->hide();
	endButton->hide();

	m_countTimer->start();
	m_repeatTimer->start();
	return true;
	});


	
	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool 
	{
		endGame();
		return true;
	});


	// 전체 게임 시간
	m_countTimer = Timer::create(60.f); // 문제 풀이 시간 
	showTimer(m_countTimer);

	m_countTimer->setOnTimerCallback([&](TimerPtr timer)->bool 
	{
		m_repeatTimer->stop();
		showMessage("실패!!");
		endButton->show();
		return true;
	});

	
	//while문 대체할 타이머 
	m_repeatTimer->setOnTimerCallback([&](TimerPtr timer)->bool 
	{

		//화면 안의 현재 도형 좌표 변경 + 현재 도형이 바닥에 닿았을 시, 스테이지 좌표 블럭처리 후 다음 도형으로 변경처리
		// 화면 위로 블럭이 넘어간  경우
		if (!CShapeManager::GenInst()->Update())
		{
			m_repeatTimer->stop();
			m_countTimer->stop();
			endButton->show();
			showMessage("실패!!!");
			return true;
			
		}

		// stage에 쌓인 블럭 화면에 출력 
		// 3줄 이상 블럭 격파 시 성공
		if (CStageManager::GenInst()->Run())
		{
			m_repeatTimer->stop();
			m_countTimer->stop();
			endButton->show();
			showMessage("성공!!!");
			return true;
		}

		// 좌표 변경된 화면 안의 현재 도형 출력 
		CShapeManager::GenInst()->Render();
		

		timer->set(0.3f);
		timer->start();

		return true;
	});


	//3. 게임 시작
	startGame(m_scene);



	return 0;
}

