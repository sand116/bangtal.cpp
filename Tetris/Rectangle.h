#pragma once
# include "Shape.h"

class CRectangle: public CShape
{

public :
	CRectangle();
	~CRectangle();

	bool Init();
	virtual int getColor();

};

