#include "Core.h"
#include "StageManager.h"
#include "ShapeManager.h"

CCore* CCore::m_pInst = NULL;

// �����ڿ� ������� ���� �ε��� ����ǹǷ� �̸� �ʱ�ȭ  

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
	//�ܼ�â �ڵ� ����
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_hConsole == INVALID_HANDLE_VALUE)
		return false;

	// ** ȭ�� ����
	m_scene = Scene::create("��Ʈ����", "picture/scene.png");

	// ��ü ���� �ð�
	m_countTimer = Timer::create(30.f); // ���� Ǯ�� �ð� 

	//while ���� ����� Ÿ�̸�
	m_repeatTimer = Timer::create(0.1f);

	// �������� �����ڸ� ���� �� �ʱ�ȭ�Ѵ�
	if (!CStageManager::GenInst()->Init()) return false;

	return true;
}


void CCore::Run()
{

	m_repeatTimer->setOnTimerCallback([&](TimerPtr timer)->bool {

		// Ŭ���������������� �ܼ� ��ǥ ���� �ʱ�ȭ���� �ʾ� stage�� ������
		system("cls");

		/*ȭ�� ���� ���� ���� ��ǥ ���� + ���� ������ �ٴڿ� ����� ��,
		   �������� ��ǥ ��ó�� �� ���� �������� ����ó��
		*/
		CShapeManager::GenInst()->Update();

		// stage�� ���� �� ȭ�鿡 ���
		CStageManager::GenInst()->Run();

		// ��ǥ ����� ���� ���� ȭ�鿡 ��� 
		CShapeManager::GenInst()->Render();

		});
}


// ������ �ֻܼ� ��ǥ �������ִ� �Լ�
void CCore::SetConsolePos(int x, int y)
{	
	//��ĭ�� 2����Ʈ�� ����Ѵ�. �׷��� ������ *2�� ���ش�.

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