////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_


////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

	void MouseMove(int x, int y);
	int GetMouseDeltaX();
	int GetMouseDeltaY();
	void ResetMouseDelta(); // 한 프레임마다 초기화

	void ClearAllKeys();


private:
	bool m_keys[256];
	int m_mouseX, m_mouseY;
	int m_prevMouseX, m_prevMouseY;
	int m_deltaX, m_deltaY;
};

#endif