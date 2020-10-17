#pragma once

#include "value.h"
#include "macro.h"
#include <bangtal>
using namespace bangtal;

class CShapeManager
{
private:
	CShapeManager();
	~CShapeManager();

private:
	static CShapeManager* m_pInst;
	int speed = 0;
public:
	static CShapeManager* GenInst() 
	{
		// staic 객체 반환
		if (!m_pInst) m_pInst = new CShapeManager;
		return m_pInst;
	}
	static void DestroyInst() 
	{
		SAFE_DELETE(m_pInst);
	}

private:

	
	//현재 나와있는 도형을 표현한다
	class CShape* m_pCurShape;
	
	//다음에 나올 도형을 표현한다
	class CShape* m_pNextShape;

	//도형을 움직일 틱을 정한다
	int m_iSpeed;
public:
	//도형 만드는 기능 
	bool Update();
	void Render();
	class CShape* CreateRamdomShape();
	class CShape* CreateShape(SHAPE_TYPE eType);
};
