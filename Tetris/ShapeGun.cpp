#include "ShapeGun.h"



CShapeGun::CShapeGun()
{
}

CShapeGun::~CShapeGun()
{
}

bool CShapeGun::Init()
{
	m_cShape[2][0] = '1';
	m_cShape[2][1] = '1';
	m_cShape[2][2] = '1';
	m_cShape[3][2] = '1';
	m_iWidthCount = 3;
	m_tPos.x = 4;
	m_tPos.y = 0;
	m_iDir = RD_LEFT;

	return true;
}

//로테이션을 누를때마다
void CShapeGun::Rotation()
{
	++m_iDir;
	m_iDir %= RD_END;

	// 다 빈 공간 처리 후 다시 구성
	for (int i = 0; i < 4; ++i) 
	{
		for (int j = 0; j < 4; ++j)
		{
			m_cShape[i][j] = '0';
		}
	}
	switch (m_iDir)
	{
		case RD_UP :
			m_cShape[1][1] = '1';
			m_cShape[2][1] = '1';
			m_cShape[3][1] = '1';
			m_cShape[3][0] = '1';
			m_iWidthCount = 2;
			break;
		case RD_RIGHT:
			m_cShape[2][0] = '1';
			m_cShape[3][0] = '1';
			m_cShape[3][1] = '1';
			m_cShape[3][2] = '1';
			m_iWidthCount = 3;
			break;
		case RD_DOWN:
			m_cShape[1][0] = '1';
			m_cShape[2][0] = '1';
			m_cShape[3][0] = '1';
			m_cShape[1][1] = '1';
			m_iWidthCount = 2;
			break;
		case RD_LEFT:
			m_cShape[2][0] = '1';
			m_cShape[2][1] = '1';
			m_cShape[2][2] = '1';
			m_cShape[3][2] = '1';
			m_iWidthCount = 3;
			break;
	}
}
int CShapeGun::getColor()
{
	return ST_GUN;

}
