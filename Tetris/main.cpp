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
		// 화면 위로 블럭이 넘어간 경우
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
/*
	1분 안에 테트리스 4줄 이상 격파 시 성공하도록 처리하는 게임


	* main함수

		- 배경화면 초기화 -> 배경화면에 있는 스타트버튼을 클릭하면, 스테이지 관리자 클래스 생성하고 init함수 호출
		- 스타트 게임 함수 호출 및 게임 진행


		0.5초짜리 타이머가 끝날때마다
		{
			1. 도형 관리자 클래스 update 함수 호출 : stage안에 현재 도형 위치를 업데이트하는 것으로, stage 좌표에 표시한다.

				-> 현재 도형을 계속 바닥으로 내림

				-> 만약 바닥에 닿았을 때나 & 쌓이는 경우 스테이지 좌표에 해당 블럭 처리 : stage클래스에 블럭 처리할 좌표 전달하여 처리 맡김

				-> 현재 도형이 키보드 a를 받으면 왼쪽, d를 받으면 오른쪽, w를 받으면 도형이 변경되도록 콜백함수 처리함

				->다음 도형 생성하고 다음 도형을 현재 도형으로 바꾼 후 현재 도형을 상위 초기 위치로 변경



			2. 스테이지 클래스 render 함수 호출

				- stage 내부에 쌓인 블럭들 출력 (좌표상 2로 처리된 경우)

				- 다음 도형 모양 출력

			3. 도형 관리자에서 현재 도형 위치를 출력

		}

	* 스테이지 관리자 클래스 -> 스테이지 관리
	*
	* 스테이지 클래스 -> 스테이지 좌표(10,15) 가짐

		- init함수 : 좌표 초기화
		- render함수 : 좌표에 쌓인 블럭 출력 - 하얀색 블록 출력
		- checkBlock 함수 : 해당 블럭이 좌표에 쌓인 블럭인지 체크
		- addBlock 함수 : 해당 블럭을 좌표에 쌓는 함수

	* 도형 관리자 클래스  -> 현재 도형 클래스, 다음 도형 클래스를 가짐
		- update함수 : 현재 도형의 움직임 제어
		- init함수 : 현재 도형 클래스 생성 및 초기화
		- move 함수 : 옆으로, 아래로 움직이도록 제어
		- render 함수 : 현재 도형 & 다음 도형 출력

	* 도형 클래스
		- CShape 클래스 상속 받은 7가지 도형으로 구성 -> 모양만 다르고 다른 제어 기능은 같음.
		- 각 도형마다 회전 시 모양이 달라지는 좌표가 다르기 때문에 해당 회전 기능을 처리하는 ROTATION함수 VIRTUAL 처리


*/
