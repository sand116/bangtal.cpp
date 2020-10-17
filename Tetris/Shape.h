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
	POSITION m_tPos; // 스테이지 상의 위치(계속 변경)
	POSITION m_tPivot; // [4][4] 칸 안의 기준 점 : 기본적으로 바닥
	int m_iWidthCount; //가로 몇칸인지
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

	// shape을 상속받는 모양마다 다른 경우 virtual로 선언
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


