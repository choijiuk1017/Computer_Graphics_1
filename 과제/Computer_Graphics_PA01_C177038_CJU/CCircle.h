#pragma once
#include "CShape.h"

//원을 그리는 클래스
class CCircle : public CShape
{
private:
	float m_r;

public:
	CCircle(float x, float y, float r);

	~CCircle()
	{

	}

	void Draw() const;
};

