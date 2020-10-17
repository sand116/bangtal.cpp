#pragma once
#include "value.h"
#include <bangtal>
using namespace bangtal;
class CShape
{
public:
	CShape();
	virtual ~CShape();
private:
	friend class ShapeManager;

protected:
	char m_cShape[4][4];
	POSITION m_tPos; // �������� ���� ��ġ(��� ����)
	POSITION m_tPivot; // [4][4] ĭ ���� ���� �� : �⺻������ �ٴ�
	int m_iWidthCount; //���� ��ĭ����
	int m_iDir;

public :

	char GetBlock(int x, int y) const
	{
		return m_cShape[y][x];
	}

	void SetPosition(int x, int y)
	{
		m_tPos.x = x;
		m_tPos.y = y;

	}
	void SetPosition(const POSITION& tPos)
	{
		m_tPos = tPos;
	}
	POSITION GetPosition(void)
	{
		return m_tPos;
	}

public :

	// shape�� ��ӹ޴� ��縶�� �ٸ� ��� virtual�� ����
	virtual bool Init();
	virtual void Rotation();
	virtual int getColor()=0;

public :
	int MoveDown();
	void MoveLeft();
	void MoveRight();
	void Render();
	void RenderNext();
;

};


