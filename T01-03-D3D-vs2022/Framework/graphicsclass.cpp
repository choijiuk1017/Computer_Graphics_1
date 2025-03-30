////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////

// �׷��� ó�� ��� Ŭ����
// ���������� D3DClass�� �̿��� Direct3D �ʱ�ȭ
// ��ü �ý����� �׷��� ó�� ����ž ����

#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}

// �׷��� �ý��� ��ü �ʱ�ȭ
bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	// D3D ��ü ����
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	// Direct3D �ʱ�ȭ
	// (ȭ�� �ʺ�, ȭ�� ����, ȭ�� ���� ���� �ѱ�/����, ������ �ڵ�(Direct3D�� �׸� â), ��ü ȭ�� ����, z ���� �ִ� ����, ī�޶� ����� z��) ����
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	return true;
}

// ������ ȣ��
// ���� ���ҽ� ���� �� ������ ����
void GraphicsClass::Shutdown()
{
	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

// �� ������ ���� ȣ��
// ���� ������ ����
bool GraphicsClass::Frame()
{
	bool result;


	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

// ���� ȭ�鿡 �׸��� ó��
bool GraphicsClass::Render()
{
	// Clear the buffers to begin the scene.
	// ȭ���� ���� ������ ����(�ʱ�ȭ)
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	// Add codes here for rendering
	// ���߿� �ﰢ��, �ؽ�ó, �׸� �� �߰� ����

	// Present the rendered scene to the screen.
	// ����� ������ ȭ�鿡 ���
	m_D3D->EndScene();

	return true;
}