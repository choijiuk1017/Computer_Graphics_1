////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////

// 그래픽 처리 담당 클래스
// 냅부적으로 D3DClass를 이용해 Direct3D 초기화
// 전체 시스템의 그래픽 처리 제어탑 역할

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

// 그래픽 시스템 전체 초기화
bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	// D3D 객체 생성
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	// Direct3D 초기화
	// (화면 너비, 화면 높이, 화면 찢김 방지 켜기/끄기, 윈도우 핸들(Direct3D가 그릴 창), 전체 화면 여부, z 버퍼 최대 깊이, 카메라에 가까운 z값) 설정
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	return true;
}

// 끝나면 호출
// 내부 리소스 해제 및 포인터 삭제
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

// 매 프레임 마다 호출
// 실제 렌더링 수행
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

// 실제 화면에 그리는 처리
bool GraphicsClass::Render()
{
	// Clear the buffers to begin the scene.
	// 화면을 지정 색으로 지움(초기화)
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	// Add codes here for rendering
	// 나중에 삼각형, 텍스처, 그림 등 추가 가능

	// Present the rendered scene to the screen.
	// 백버퍼 내용을 화면에 출력
	m_D3D->EndScene();

	return true;
}