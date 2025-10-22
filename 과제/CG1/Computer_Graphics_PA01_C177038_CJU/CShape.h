#pragma once
#include<Windows.h>

// CShape 클래스
class CShape
{	
// CRectangle, CCircle 클래스에서 m_x, m_y의 값을 변동시키지 않기 때문에 데이터 보호가 필요없을 것 같아 Get, Set 함수를 따로 생성하지 않고 변수들을 protected로 선언하였습니다.
protected:
	float m_x;
	float m_y;

public:
	CShape(float x, float y);

	virtual ~CShape()
	{
		
	}

	virtual void Draw() const
	{

	
	}
};