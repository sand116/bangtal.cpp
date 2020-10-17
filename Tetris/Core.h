#pragma once

#include "value.h"
#include "macro.h"
#include <windows.h>
#include <bangtal>

using namespace bangtal;


// 전체 프로젝트를 관리
class CCore
{
public :
	CCore();
	~CCore();


private :
	static CCore* m_pInst; // static멤버변수로 클래스 로딩시점에 한번만 호출 
	ScenePtr m_scene;
	time_t m_startTime;
	TimerPtr m_countTimer;
	TimerPtr m_repeatTimer;


;public :
	// 싱글톤 패턴 - core 객체 반환
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

