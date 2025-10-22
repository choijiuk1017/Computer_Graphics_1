////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "inputclass.h"


InputClass::InputClass()
{
}


InputClass::InputClass(const InputClass& other)
{
}


InputClass::~InputClass()
{
}


void InputClass::Initialize()
{
	int i;
	

	// Initialize all the keys to being released and not pressed.
	for(i=0; i<256; i++)
	{
		m_keys[i] = false;
	}
	m_mouseX = m_mouseY = 0;
	m_prevMouseX = m_prevMouseY = 0;
	m_deltaX = m_deltaY = 0;

	return;
}


void InputClass::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;

	return;
}


void InputClass::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
	return;
}


bool InputClass::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}

void InputClass::MouseMove(int x, int y)
{

	m_deltaX = x - m_prevMouseX;
	m_deltaY = y - m_prevMouseY;

	m_prevMouseX = x;
	m_prevMouseY = y;

	m_mouseX = x;
	m_mouseY = y;
}

int InputClass::GetMouseDeltaX() { return m_deltaX; }
int InputClass::GetMouseDeltaY() { return m_deltaY; }

void InputClass::ResetMouseDelta()
{
	m_deltaX = 0;
	m_deltaY = 0;
}

