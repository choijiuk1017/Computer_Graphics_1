#pragma once
#include<Windows.h>

// CShape Ŭ����
class CShape
{	
// CRectangle, CCircle Ŭ�������� m_x, m_y�� ���� ������Ű�� �ʱ� ������ ������ ��ȣ�� �ʿ���� �� ���� Get, Set �Լ��� ���� �������� �ʰ� �������� protected�� �����Ͽ����ϴ�.
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