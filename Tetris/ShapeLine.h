#pragma once
# include "Shape.h"
class CShapeLine : public CShape
{
public:
	CShapeLine();
	~CShapeLine();
	bool Init();
	virtual void Rotation();
	virtual int getColor();

};

