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

/*내려가는 행위  제어 및 도형이 키보드 입력 받을 때 움직임을 제어  
업데이트가 열번 호출되어야 한번 move down 되도록 한다.
*/

bool CShapeManager::Update()
{	
	//현재 스테이지를 얻어옴
	CStage* pStage = CStageManager::GenInst()->GetCurStage();
	speed++;

	//speed -> 내려가는 속도 제어
	if (speed == 2) {
		//도형이 바닥에 닿았을 때 true를 리턴한다
		if (m_pCurShape->MoveDown() == 1)
		{
			//블럭을 쌓는다.
			pStage->AddBlock(m_pCurShape, m_pCurShape->GetPosition());

			SAFE_DELETE(m_pCurShape);


			m_pCurShape = m_pNextShape; // 다음 도형 전달 
			m_pCurShape->SetPosition(4, 0); // 다음 도형 화면 안으로 세팅

			m_pNextShape = CreateRamdomShape(); // 다음 next도형 생성
		}

		// 화면 밖으로 범위가 넘어갔을때 
		else if (m_pCurShape->MoveDown() == 2) return false;


		speed = 0;
	}

	// 키보드 처리 
	pStage->GetScene()->setOnKeyboardCallback([&](ScenePtr scene, int key, bool pressed)->bool {

		if (key == 1 && !pressed) m_pCurShape->MoveLeft();
		if (key == 4 && !pressed) m_pCurShape->MoveRight();
		if (key == 23 && !pressed) m_pCurShape->Rotation();

		return true;
		});
	return true;

}

// 도형들을 화면 안에 출력
void CShapeManager::Render()
{	


	//현재 도형 출력 - 해당 함수가 호출될 때마다 현재 도형 위치는 계속 바뀌기 때문에 아래로 내려갈 것임
	m_pCurShape->Render();

	//대기 칸 안에 다음 도형 출력 - 도형 위치 고정
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
