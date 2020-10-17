#pragma once
# include "Shape.h"
class CShapeS : public CShape
{
public:
	CShapeS();
	~CShapeS();

	bool Init();
	virtual void Rotation();
	virtual int getColor();

};

