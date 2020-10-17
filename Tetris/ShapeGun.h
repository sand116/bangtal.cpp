#pragma once
# include "Shape.h"
class CShapeGun : public CShape
{
	public:
		CShapeGun();
		~CShapeGun();
	public:
		bool Init();
		virtual void Rotation();
		virtual int getColor();
};

