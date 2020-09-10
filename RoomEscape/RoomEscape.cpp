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
	
	// scene1으로 다시 이동하는 문
	auto door2 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270, true);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	// 거울 뒤에 문을 숨긴다
	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 910, 270);

	auto mirror = Object::create("Images/거울.png", scene2, 830, 210, true);
	mirror->setScale(0.6f);
	auto mirror_moved = false;

	mirror->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (mirror_moved == false) {
			showMessage("거울에 글씨가 적혀 있다. \n 1. 개미 2. 사자 3. 사람 \n 무슨 공통점이 있을까?");
		}
		else {
			mirror->locate(scene2, 1000, 210);
			showMessage("스르륵 ~ 문이 나타났다. ");
		}
		return true;
	});

	mirror->setOnKeypadCallback([&](ObjectPtr object)->bool {
		showMessage("거울이 움직이는 것 같다.");
		mirror_moved = true;
		return true;
		});

	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame(); //문이 열린 상태
		return true;
		});


	// 키패드를 만든다.
	auto keypad = Object::create("Images/키패드.png", scene2, 750, 420);
	keypad->setScale(1.5f);
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("642", mirror);
		return true;
		}); 



	// 2. 게임을 시작한다.
	startGame(scene1);

	return 0;
}

