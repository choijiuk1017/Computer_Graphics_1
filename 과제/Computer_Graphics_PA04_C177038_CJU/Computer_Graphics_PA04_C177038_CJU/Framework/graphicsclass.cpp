////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_TextureShader = 0;

	m_Bitmap = 0;
	m_Title = 0;
	m_ShowTitle = false;

}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	XMMATRIX baseViewMatrix;

	std::wstring objPaths[11] = {
		L"./data/Old House.obj",
		L"./data/ground.obj",
		L"./data/tank 1.obj",
		L"./data/TANK 2 BODY.obj",
		L"./data/TANK 2 HEAD.obj",
		L"./data/abandonhouse.obj",
		L"./data/man.obj",
		L"./data/bombardino.obj",
		L"./data/Old House.obj",
		L"./data/truck_Launcher.obj",
		L"./data/truck_body.obj"
	};

	std::wstring texPaths[11] = {
		L"./data/Old House.dds",
		L"./data/Ground.dds",
		L"./data/Tank 1.dds",
		L"./data/Tank2Body.dds",
		L"./data/Tank2Head.dds",
		L"./data/AbHouse_Base_Color.dds",
		L"./data/10595_Military_Action_Figure_SG_v1_diffuse.dds",
		L"./data/bombardino.dds",
		L"./data/Old House.dds",
		L"./data/truck_Launcher.dds",
		L"./data/truck_body.dds"
	};

	int instanceCount[11] = {1, 1, 1, 1, 1, 1, 10, 1, 1, 1, 1};

	int objSum = 0;
	for (int i = 0; i < 11; ++i) {
		objSum += instanceCount[i];
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 10.0f, -5.0f);
	
	int polyNum = 0;

	for (int i = 0; i < 11; i++) {
		ModelClass* model = new ModelClass;
		if (!model) return false;

		bool result = model->Initialize(m_D3D->GetDevice(), objPaths[i].c_str(), texPaths[i].c_str(), instanceCount[i]);
		if (!result) {
			MessageBox(hwnd, L"Could not initialize model object.", L"Error", MB_OK);
			delete model;
			return false;
		}
		m_Models.push_back(model);

		polyNum += m_Models[i]->GetIndexCount();
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	XMMATRIX bitMapMatrix = XMMatrixIdentity();
	bitMapMatrix *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}
	// Initialize the bitmap object.
	m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/Sky.dds", 800, 800, bitMapMatrix);
	

	m_Title = new BitmapClass;
	if (!m_Title)
	{
		return false;
	}
	m_Title->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/title.dds", 800, 600, bitMapMatrix);
	

	m_BillboardModel = new ModelClass;
	if (!m_BillboardModel)
	{
		return false;  
	}

	m_BillboardModel->Initialize(m_D3D->GetDevice(), L"./data/Flame.obj", L"./data/Flame.dds", 1);

	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);


	for (int i = 0; i < 5; i++)
	{
		TextClass* text = new TextClass;
		if (!text) return false;

		bool result = text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
		if (!result) {
			MessageBox(hwnd, L"Could not initialize model object.", L"Error", MB_OK);
			delete text;
			return false;
		}
		m_Texts.push_back(text);
	}

	result = m_Texts[2]->SetObjectNum(objSum, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Texts[3]->SetPolygonNum(polyNum, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Texts[4]->SetScreenResolution(screenWidth, screenHeight, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	for (auto model : m_Models)
	{
		if (model)
		{
			model->Shutdown();
			delete model;
		}
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	if (m_Title)
	{
		m_Title->Shutdown();
		delete m_Title;
		m_Title;
	}

	if (m_BillboardModel)
	{
		m_BillboardModel->Shutdown();
		delete m_BillboardModel;
		m_BillboardModel = 0;
	}

	return;
}


bool GraphicsClass::Frame(int fps, int cpu)
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the frames per second.
	result = m_Texts[0]->SetFPS(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Texts[1]->SetCPU(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}


	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, translateMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);

	m_D3D->GetWorldMatrix(worldMatrix);

	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	XMMATRIX identity = XMMatrixIdentity();

	
	
	if(!m_ShowTitle)
	{
		m_D3D->TurnZBufferOff();

		

		// 항상 배경 먼저 렌더링
		result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, 0);
		if (!result) return false;

		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), 1,
			identity, identity, orthoMatrix, m_Bitmap->GetTexture());
		if (!result) return false;

		m_D3D->TurnOnAlphaBlending();
		
		for (int i = 0; i < 5; i++)
		{
			// Render the text strings.
			result = m_Texts[i]->Render(m_D3D->GetDeviceContext(), identity, orthoMatrix);
			if (!result)
			{
				return false;
			}
		}
		

		// Turn off alpha blending after rendering the text.
		m_D3D->TurnOffAlphaBlending();

		m_D3D->TurnZBufferOn();

	}






		
	for (int i = 0; i < 11; i++)
	{
		XMMATRIX modelworldMatrix = m_Models[i]->GetWorldMatrix();

		m_Models[i]->Render(m_D3D->GetDeviceContext());


		switch (i)
		{
		case 0:
			// 오래된 건물
			modelworldMatrix = XMMatrixScaling(0.03f, 0.03f, 0.03f)
				* XMMatrixRotationY(-XM_PI / 2) 
				* XMMatrixTranslation(-90.0f, -14.0f, 60.0f);
			break;

		case 1:
			// 바닥 지형
			modelworldMatrix = XMMatrixScaling(0.3f, 0.3f, 0.3f)
				* XMMatrixTranslation(0.0f, -30.0f, 0.0f);

			break;

		case 2:
			// 탱크 1
			modelworldMatrix = XMMatrixScaling(0.2f, 0.2f, 0.2f)
				* XMMatrixRotationY(-XM_PI / 2) 
				* XMMatrixRotationZ(XM_PI / 12) 
				* XMMatrixTranslation(-50.0f, -28.0f, 0.0f);
			break;

		case 3:
			// 탱크 2 몸체
			modelworldMatrix = XMMatrixScaling(0.2f, 0.2f, 0.2f)
				* XMMatrixRotationY(-XM_PI / 3) 
				* XMMatrixRotationZ(XM_PI / 6) 
				* XMMatrixTranslation(0.0f, -10.5f, 0.0f);
			break;
		case 4:
			// 탱크 2 머리
			modelworldMatrix = XMMatrixScaling(0.2f, 0.2f, 0.2f)
				* XMMatrixRotationY(rotation * 0.08) 
				* XMMatrixRotationZ(XM_PI / 6) 
				* XMMatrixTranslation(1.0f, -9.5f, -1.0f);
			break;
		case 5:
			// 부서진 집
			modelworldMatrix = XMMatrixScaling(0.03f, 0.03f, 0.03f)
				* XMMatrixRotationY(XM_PI / 2) 
				* XMMatrixTranslation(-30.0f, -30.0f, 100.0f);
			break;
		case 6:
			// 사람
			modelworldMatrix = XMMatrixScaling(0.14f, 0.14f, 0.14f)
				* XMMatrixRotationY(-XM_PI / 2) 
				* XMMatrixTranslation(-80.0f, -25.0f, 50.0f);
			break;
		case 7:
			// 전투기
			modelworldMatrix =  XMMatrixScaling(0.1f, 0.1f, 0.1f)
				* XMMatrixRotationZ(XM_PI / 6)  
				* XMMatrixTranslation(70.0f, 0.0f, 0.0f) 
				* XMMatrixRotationY(rotation * 0.5f) 
				* XMMatrixTranslation(0.0f, 50.0f, 0.0f);
			break;
		case 8:
			// 오래된 건물
			modelworldMatrix = XMMatrixScaling(0.03f, 0.03f, 0.03f)
				* XMMatrixRotationY(-XM_PI / 2)
				* XMMatrixTranslation(-90.0f, -14.0f, -30.0f);
			break;
		case 9:
			//트럭 런처
			modelworldMatrix = XMMatrixScaling(0.1f, 0.1f, 0.1f)
				* XMMatrixRotationY(rotation * 0.08)
				* XMMatrixTranslation(89.0f, -26.0f, -12.0f);
			break;
		case 10:
			modelworldMatrix = XMMatrixScaling(0.1f, 0.1f, 0.1f)
				* XMMatrixTranslation(90.0f, -26.0f, -30.0f);
			break;
		}
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(), m_Models[i]->GetInstanceCount(),
			modelworldMatrix, viewMatrix, projectionMatrix, m_Models[i]->GetTexture());

		if (!result) return false;
	}

	XMMATRIX billboardingMatrix = m_BillboardModel->GetWorldMatrix();
	XMFLOAT3 cameraPosition, modelPosition;
	// 카메라 위치를 얻는다.
	cameraPosition = m_Camera->GetPosition();

	// 빌보드 모델의 위치를 ​​설정합니다.
	modelPosition.x = -2.0f;
	modelPosition.y = -1.5f;
	modelPosition.z = 1.0f;

	double angle = atan2(modelPosition.x - cameraPosition.x, modelPosition.z - cameraPosition.z) * (180.0 / XM_PI);


	float Brotation = (float)angle * 0.0174532925f;

	
	billboardingMatrix = XMMatrixScaling(0.05f, 0.05f, 0.05f) * XMMatrixRotationY(Brotation);


	translateMatrix = XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);


	billboardingMatrix = XMMatrixMultiply(billboardingMatrix, translateMatrix);


	m_BillboardModel->Render(m_D3D->GetDeviceContext());
	 
	if (!m_TextureShader->Render(m_D3D->GetDeviceContext(), m_BillboardModel->GetIndexCount(), 1, billboardingMatrix, viewMatrix, projectionMatrix,
		m_BillboardModel->GetTexture()))
	{
		return false;
	}


	if (m_ShowTitle)
	{
		m_D3D->TurnZBufferOff();
		
		XMMATRIX titleMatrix = XMMatrixTranslation(0.0f, 0.0f, -100.0f);
		result = m_Title->Render(m_D3D->GetDeviceContext(), 0, 0);
		if (!result) return false;

		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Title->GetIndexCount(), 1,
			titleMatrix, identity, orthoMatrix, m_Title->GetTexture());
		if (!result) return false;

	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}



