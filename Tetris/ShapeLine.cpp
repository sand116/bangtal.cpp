#include "ShapeLine.h"
CShapeLine::CShapeLine()
{
}

CShapeLine::~CShapeLine()
{
}

bool CShapeLine::Init()
{
	m_cShape[3][0] = '1';
	m_cShape[3][1] = '1';
	m_cShape[3][2] = '1';
	m_cShape[3][3] = '1';
	m_iWidthCount = 4;
	m_tPos.x = 4;
	m_tPos.y = 0;
	m_iDir = RD_DOWN;
	return true;
}


void CShapeLine::Rotation()
{
	m_iDir = m_iDir == RD_DOWN ? RD_UP : RD_DOWN;

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
	case RD_UP:
		m_cShape[0][0] = '1';
		m_cShape[1][0] = '1';
		m_cShape[2][0] = '1';
		m_cShape[3][0] = '1';
		m_iWidthCount = 1;
		break;

	case RD_DOWN:
		m_cShape[3][0] = '1';
		m_cShape[3][1] = '1';
		m_cShape[3][2] = '1';
		m_cShape[3][3] = '1';
		m_iWidthCount = 4;
		break;

	}
}
int CShapeLine::getColor()
{
	return ST_LINE;

}
