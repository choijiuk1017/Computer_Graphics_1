#pragma once
#include "CShape.h"

//사각형을 그리는 클래스
class CRectangle : public CShape
{
private:
	float m_w;
	float m_h;

public:
	CRectangle(float x, float y, float w, float h);

	~CRectangle()
	{

	}

	void Draw() const;
};

