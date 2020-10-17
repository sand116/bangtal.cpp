#include "Core.h"
#include "StageManager.h"
#include "ShapeManager.h"

CCore* CCore::m_pInst = NULL;

// 생성자와 상관없이 최초 로딩시 수행되므로 미리 초기화  

CCore::CCore() :m_bLoop(true),m_scene(NULL)
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	srand((unsigned int)time(NULL));
	srand(time(0));
}
CCore::~CCore()
{
	CStageManager::DestroyInst();

}

bool CCore::Init()
{	
	//콘솔창 핸들 생성
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_hConsole == INVALID_HANDLE_VALUE)
		return false;

	// ** 화면 생성
	m_scene = Scene::create("테트리스", "picture/scene.png");

	// 전체 게임 시간
	m_countTimer = Timer::create(30.f); // 문제 풀이 시간 

	//while 문을 대신할 타이머
	m_repeatTimer = Timer::create(0.1f);

	// 스테이지 관리자를 생성 및 초기화한다
	if (!CStageManager::GenInst()->Init()) return false;

	return true;
}


void CCore::Run()
{

	m_repeatTimer->setOnTimerCallback([&](TimerPtr timer)->bool {

		// 클리어해주지않으면 콘솔 좌표 설정 초기화되지 않아 stage도 내려감
		system("cls");

		/*화면 안의 현재 도형 좌표 변경 + 현재 도형이 바닥에 닿았을 시,
		   스테이지 좌표 블럭처리 후 다음 도형으로 변경처리
		*/
		CShapeManager::GenInst()->Update();

		// stage에 쌓인 블럭 화면에 출력
		CStageManager::GenInst()->Run();

		// 좌표 변경된 현재 도형 화면에 출력 
		CShapeManager::GenInst()->Render();

		});
}


// 도형의 콘솔상 좌표 설정해주는 함수
void CCore::SetConsolePos(int x, int y)
{	
	//한칸은 2바이트를 사용한다. 그렇기 때문에 *2를 해준다.

	COORD pos = { 2*(x+1),y };
	SetConsoleCursorPosition(m_hConsole, pos);
	return;
}

void CCore::End()
{
	m_bLoop = false;
	return;
}

ScenePtr CCore::getScene() {
	return scene;
}