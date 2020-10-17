#pragma once

#include "value.h"
#include "macro.h"
#include <windows.h>
#include <bangtal>

using namespace bangtal;


// ��ü ������Ʈ�� ����
class CCore
{
public :
	CCore();
	~CCore();


private :
	static CCore* m_pInst; // static��������� Ŭ���� �ε������� �ѹ��� ȣ�� 
	ScenePtr m_scene;
	time_t m_startTime;
	TimerPtr m_countTimer;
	TimerPtr m_repeatTimer;


;public :
	// �̱��� ���� - core ��ü ��ȯ
	static CCore* GenInst() {
		if (!m_pInst) m_pInst = new CCore;
		return m_pInst;
	}

	static void DestroyInst() {
		SAFE_DELETE(m_pInst);
	}

	ScenePtr getScene();
private :
	HANDLE m_hConsole;
	bool m_bLoop;
public :
	bool Init();
	void Run();
	void SetConsolePos(int x, int y);
	void End();
};

