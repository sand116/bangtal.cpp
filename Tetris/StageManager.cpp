#include "StageManager.h"
#include "Stage.h"

CStageManager* CStageManager::m_pInst = NULL; 

CStageManager::CStageManager() : m_pCurStage(NULL) // 스테이지 지역 변수 초기화
{
}

CStageManager::~CStageManager()
{
}


bool CStageManager::Init(const ScenePtr scene)
{
	m_pCurStage = new CStage; //스테이지 객체 생성
	if (!m_pCurStage->Init(scene)) return false;
	return true;
}

bool CStageManager::Run()
{
	return m_pCurStage->Render();
}

CStage* CStageManager::GetCurStage() const
{
	return m_pCurStage;
}
