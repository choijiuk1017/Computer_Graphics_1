#include "CCircle.h"

CCircle::CCircle(float x, float y, float r) : CShape(x, y), m_r(r)
{

}

void CCircle::Draw() const
{
	HDC hdc = GetWindowDC(GetForegroundWindow());

	Ellipse(hdc, m_x - m_r, m_y - m_r, m_x + m_r, m_y + m_r);
}