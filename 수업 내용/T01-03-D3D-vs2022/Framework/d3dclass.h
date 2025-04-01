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
	bool m_vsync_enabled; // vsync(ȭ�� ���� ����)�� ų ���� ����
		
	int m_videoCardMemory; // �׷��� ī�� �޸� (MB ����)
	char m_videoCardDescription[128]; // �׷��� ī�� �̸�
	unsigned int m_refreshRateNumerator; // ����� �ֻ��� ����
	unsigned int m_refreshRateDenominator; // ����� �ֻ��� ����
	 
	ID3D11Device* m_device; // Direct 3D ����̽�(GPU �۾���)
	ID3D11DeviceContext* m_deviceContext; // �۾��� �����ϴ� ���ؽ�Ʈ

	IDXGISwapChain* m_swapChain; // �׸� ȭ���� ����Ϳ� �׷��ִ� ���� ü��
	ID3D11RenderTargetView* m_renderTargetView; // �� ���� ��(���� �׸��� �׸��� ���)

	ID3D11Texture2D* m_depthStencilBuffer; // ����/���ٽ� �� ����
	ID3D11DepthStencilState* m_depthStencilState; // ����/���ٽ� �˻� ��Ģ
	ID3D11DepthStencilView* m_depthStencilView; // ����/���ٽ� �� ��

	ID3D11RasterizerState* m_rasterState; // �������� �ȼ��� �ٲ� ���� ��Ģ
};

#endif