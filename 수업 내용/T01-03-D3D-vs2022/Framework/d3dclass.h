////////////////////////////////////////////////////////////////////////////////
// Filename: d3dclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib") 

//////////////
// INCLUDES //
//////////////
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: D3DClass
////////////////////////////////////////////////////////////////////////////////
class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	bool InitializeGraphicsHW(int screenWidth, int screenHeight, bool vsync);
	bool InitializeSwapBuffer(int screenWidth, int screenHeight, HWND hwnd, bool fullscreen);
	bool InitializeDepthStencilBuffer(int screenWidth, int screenHeight);
	bool InitializeRasterizer();
	bool InitializeViewport(int screenWidth, int screenHeight);
	void Shutdown();
	
	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetVideoCardInfo(char*, int&);

private:
	bool m_vsync_enabled; // vsync(화면 찢김 방지)를 킬 건지 여부
		
	int m_videoCardMemory; // 그래픽 카드 메모리 (MB 단위)
	char m_videoCardDescription[128]; // 그래픽 카드 이름
	unsigned int m_refreshRateNumerator; // 모니터 주사율 정보
	unsigned int m_refreshRateDenominator; // 모니터 주사율 정보
	 
	ID3D11Device* m_device; // Direct 3D 디바이스(GPU 작업자)
	ID3D11DeviceContext* m_deviceContext; // 작업을 실행하는 컨텍스트

	IDXGISwapChain* m_swapChain; // 그린 화면을 모니터에 그려주는 스왑 체인
	ID3D11RenderTargetView* m_renderTargetView; // 백 버퍼 뷰(실제 그림을 그리는 대상)

	ID3D11Texture2D* m_depthStencilBuffer; // 깊이/스텐실 용 버퍼
	ID3D11DepthStencilState* m_depthStencilState; // 깊이/스텐실 검사 규칙
	ID3D11DepthStencilView* m_depthStencilView; // 깊이/스텐실 용 뷰

	ID3D11RasterizerState* m_rasterState; // 폴리곤을 픽셀로 바꿀 때의 규칙
};

#endif