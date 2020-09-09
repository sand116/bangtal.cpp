#include <bangtal.h>
#include <iostream>
using namespace bangtal;


int main()
{
	// 장면을 생성한다.
	auto scene1 = Scene::create("룸1", "Images/배경-1.png");
	auto scene2 = Scene::create("룸2", "Images/배경-2.png");


	// 문을 생성한다.
	auto open1 = false; // false - 닫힌 상태 
	auto door1 = Object::create("Images/문-오른쪽-닫힘.png", scene1, 800, 270);

	// 문을 클릭하면 이동한다. //lambda function 
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		// 문이 열린 상태이면 scene2로 전환
		// 문이 닫힌 상태이면 문을 열어준다.
		if (open1 == true) scene2->enter();
		else {
			door1->setImage("Images/문-오른쪽-열림.png");
			open1 = true;
		}
		return true;
		});

	auto door2 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270, true);

	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	// 문을 숨긴다. 불을 꺼서 문이 보이면 클릭 후 게임을 종료한다.
	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 910, 270, false);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame(); //문이 열린 상태
		return true;
		});


	// 스위치를 만든다. 불이 꺼지면 문이 보인다.
	auto button = Object::create("Images/스위치.png", scene2, 880, 440);
	auto lighted = true;
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted) { //켜진 상태 
			scene2->setLight(0.2f);
			door3->show();
			lighted = false;
		}
		else { //꺼진 상태
			scene2->setLight(1.0f);
			door3->hide();
			lighted = true;
		}
		return true;
		});


	// 2. 게임을 시작한다.
	startGame(scene1);

	return 0;
}

