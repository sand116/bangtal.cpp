#pragma once
# include "Shape.h"
class CShapeT : public CShape
{
public:
	CShapeT();
	~CShapeT();

	bool Init();
	virtual void Rotation();
	virtual int getColor();

};

