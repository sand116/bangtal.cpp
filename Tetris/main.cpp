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

	//1. �ʿ��� ��ü ���� �� �ʱ�ȭ
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	srand((unsigned int)time(NULL));
	srand(time(0));

	
	// ** ȭ�� ����
	m_scene = Scene::create("��Ʈ����", "picture/scene.png");
	auto nextButton = Object::create("picture/nextButton.png", m_scene, 790, 370);

	
	// �������� �����ڸ� ���� �� �ʱ�ȭ�Ѵ�.
	if (!CStageManager::GenInst()->Init(m_scene)) return 0;



	//while ���� ����� Ÿ�̸�
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


	// ��ü ���� �ð�
	m_countTimer = Timer::create(60.f); // ���� Ǯ�� �ð� 
	showTimer(m_countTimer);

	m_countTimer->setOnTimerCallback([&](TimerPtr timer)->bool 
	{
		m_repeatTimer->stop();
		showMessage("����!!");
		endButton->show();
		return true;
	});

	
	//while�� ��ü�� Ÿ�̸� 
	m_repeatTimer->setOnTimerCallback([&](TimerPtr timer)->bool 
	{

		//ȭ�� ���� ���� ���� ��ǥ ���� + ���� ������ �ٴڿ� ����� ��, �������� ��ǥ ��ó�� �� ���� �������� ����ó��
		// ȭ�� ���� ���� �Ѿ  ���
		if (!CShapeManager::GenInst()->Update())
		{
			m_repeatTimer->stop();
			m_countTimer->stop();
			endButton->show();
			showMessage("����!!!");
			return true;
			
		}

		// stage�� ���� �� ȭ�鿡 ��� 
		// 3�� �̻� �� ���� �� ����
		if (CStageManager::GenInst()->Run())
		{
			m_repeatTimer->stop();
			m_countTimer->stop();
			endButton->show();
			showMessage("����!!!");
			return true;
		}

		// ��ǥ ����� ȭ�� ���� ���� ���� ��� 
		CShapeManager::GenInst()->Render();
		

		timer->set(0.3f);
		timer->start();

		return true;
	});


	//3. ���� ����
	startGame(m_scene);



	return 0;
}

