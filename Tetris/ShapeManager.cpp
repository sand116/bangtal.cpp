#include "ShapeManager.h"
#include "Rectangle.h"
#include "ShapeS.h"
#include "ShapeZ.h"
#include "ShapeT.h"
#include "ShapeGUN.h"
#include "ShapeRGUN.h"
#include "ShapeLine.h"
#include "StageManager.h"
#include "Stage.h"
#include "Stage.h"
#include <windows.h>
#include <bangtal>
using namespace bangtal;

CShapeManager* CShapeManager::m_pInst = NULL;

CShapeManager::CShapeManager() :
	m_pCurShape(NULL), 
	m_pNextShape(NULL)
{
	m_pCurShape = CreateRamdomShape();
	m_pNextShape = CreateRamdomShape();
	m_iSpeed = 0;
}

CShapeManager::~CShapeManager()
{
	
	SAFE_DELETE(m_pCurShape);
	SAFE_DELETE(m_pNextShape);


}

/*�������� ����  ���� �� ������ Ű���� �Է� ���� �� �������� ����  
������Ʈ�� ���� ȣ��Ǿ�� �ѹ� move down �ǵ��� �Ѵ�.
*/

bool CShapeManager::Update()
{	
	//���� ���������� ����
	CStage* pStage = CStageManager::GenInst()->GetCurStage();
	speed++;

	//speed -> �������� �ӵ� ����
	if (speed == 2) {
		//������ �ٴڿ� ����� �� true�� �����Ѵ�
		if (m_pCurShape->MoveDown() == 1)
		{
			//���� �״´�.
			pStage->AddBlock(m_pCurShape, m_pCurShape->GetPosition());

			SAFE_DELETE(m_pCurShape);


			m_pCurShape = m_pNextShape; // ���� ���� ���� 
			m_pCurShape->SetPosition(4, 0); // ���� ���� ȭ�� ������ ����

			m_pNextShape = CreateRamdomShape(); // ���� next���� ����
		}

		// ȭ�� ������ ������ �Ѿ���� 
		else if (m_pCurShape->MoveDown() == 2) return false;


		speed = 0;
	}

	// Ű���� ó�� 
	pStage->GetScene()->setOnKeyboardCallback([&](ScenePtr scene, int key, bool pressed)->bool {

		if (key == 1 && !pressed) m_pCurShape->MoveLeft();
		if (key == 4 && !pressed) m_pCurShape->MoveRight();
		if (key == 23 && !pressed) m_pCurShape->Rotation();

		return true;
		});
	return true;

}

// �������� ȭ�� �ȿ� ���
void CShapeManager::Render()
{	


	//���� ���� ��� - �ش� �Լ��� ȣ��� ������ ���� ���� ��ġ�� ��� �ٲ�� ������ �Ʒ��� ������ ����
	m_pCurShape->Render();

	//��� ĭ �ȿ� ���� ���� ��� - ���� ��ġ ����
	m_pNextShape->RenderNext();

}

CShape* CShapeManager::CreateRamdomShape()
{
	int iType = rand() % ST_END;

	return CreateShape((SHAPE_TYPE)iType);
}

CShape* CShapeManager::CreateShape(SHAPE_TYPE eType)
{
	CShape* pShape = NULL;
	switch (eType)
	{
	case ST_RECT:
		pShape = new CRectangle;
		break;
	case ST_S:
		pShape = new CShapeS;
		break;
	case ST_T:
		pShape = new CShapeT;
		break;
	case ST_Z:
		pShape = new CShapeZ;
		break;
	case ST_GUN:
		pShape = new CShapeGun;
		break;
	case ST_RGUN:
		pShape = new CShapeRGun;
		break;
	case ST_LINE :
		pShape = new CShapeLine;
		break;
	case ST_END:
		break;
	}

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return NULL;
	}

	return pShape;
}
