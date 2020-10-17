#include "StageManager.h"
#include "Stage.h"

CStageManager* CStageManager::m_pInst = NULL; 

CStageManager::CStageManager() : m_pCurStage(NULL) // �������� ���� ���� �ʱ�ȭ
{
}

CStageManager::~CStageManager()
{
}


bool CStageManager::Init(const ScenePtr scene)
{
	m_pCurStage = new CStage; //�������� ��ü ����
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
