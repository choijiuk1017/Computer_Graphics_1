#pragma once
#include "CShape.h"

//�簢���� �׸��� Ŭ����
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

