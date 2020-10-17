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
		// staic ��ü ��ȯ
		if (!m_pInst) m_pInst = new CShapeManager;
		return m_pInst;
	}
	static void DestroyInst() 
	{
		SAFE_DELETE(m_pInst);
	}

private:

	
	//���� �����ִ� ������ ǥ���Ѵ�
	class CShape* m_pCurShape;
	
	//������ ���� ������ ǥ���Ѵ�
	class CShape* m_pNextShape;

	//������ ������ ƽ�� ���Ѵ�
	int m_iSpeed;
public:
	//���� ����� ��� 
	bool Update();
	void Render();
	class CShape* CreateRamdomShape();
	class CShape* CreateShape(SHAPE_TYPE eType);
};
