#pragma once
# include "Shape.h"
class CShapeRGun : public CShape
{
public:
	CShapeRGun();
	~CShapeRGun();

	bool Init();
	virtual void Rotation();
	virtual int getColor();

};

