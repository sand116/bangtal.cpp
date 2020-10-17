#include "Rectangle.h"

CRectangle::CRectangle()
{
}

CRectangle::~CRectangle()
{
}

bool CRectangle::Init()
{
	m_cShape[2][0] = '1';
	m_cShape[2][1] = '1';
	m_cShape[3][0] = '1';
	m_cShape[3][1] = '1';
	m_iWidthCount = 2;
	m_tPos.x = 4;
	m_tPos.y = 0;
	return true;
}

int CRectangle::getColor()
{
	return ST_RECT;
}
