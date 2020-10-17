#pragma once
# include "Shape.h"
class CShapeZ : public CShape
{
public:
	CShapeZ();
	~CShapeZ();

	bool Init();
	virtual void Rotation();
	virtual int getColor();

};

