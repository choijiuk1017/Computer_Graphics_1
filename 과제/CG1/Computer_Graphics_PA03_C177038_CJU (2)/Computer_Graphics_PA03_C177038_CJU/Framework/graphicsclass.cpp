////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_TextureShader = 0;
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
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube model
//	m_Camera->SetPosition(0.0f, 0.5f, -3.0f);	// for chair model
	
	for (int i = 0; i < 4; i++)
	{
		ModelClass* model = new ModelClass;

		m_Models.push_back(model);
	}

	//°Ë ¸ð¾ç
	if(!m_Models[0])
	{
		return false;
	}
	result = m_Models[0]->Initialize(m_D3D->GetDevice(), L"./data/Sword.obj", L"./data/Sword.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	if (!m_Models[1])
	{
		return false;
	}
	result = m_Models[1]->Initialize(m_D3D->GetDevice(), L"./data/Shield.obj", L"./data/Shield.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	if (!m_Models[2])
	{
		return false;
	}
	result = m_Models[2]->Initialize(m_D3D->GetDevice(), L"./data/Hammer.obj", L"./data/Hammer.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	if (!m_Models[3])
	{
		return false;
	}
	// Initialize the model object.
	result = m_Models[3]->Initialize2DPlane(m_D3D->GetDevice(), L"./data/a.dds");
	// result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/chair.obj", L"./data/chair_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
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

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
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
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);

	m_D3D->GetProjectionMatrix(projectionMatrix);

	for (int i = 0; i < 4; i++)
	{
		XMMATRIX worldMatrix = m_Models[i]->GetWorldMatrix();
		m_D3D->GetWorldMatrix(worldMatrix);

		m_Models[i]->Render(m_D3D->GetDeviceContext());


		switch (i)
		{
		case 0:
			worldMatrix *= XMMatrixScaling(0.01f, 0.01f, 0.01f);
			worldMatrix *= XMMatrixRotationY(rotation);
			worldMatrix *= XMMatrixTranslation(-1.5f, 0.0f, 0.0f);
		
			break;

		case 1:
			worldMatrix *= XMMatrixScaling(0.01f, 0.01f, 0.01f);
			worldMatrix *= XMMatrixRotationY(rotation);
			worldMatrix *= XMMatrixTranslation(-1.5f, -1.0f, 0.0f);
			break;

		case 2:
			worldMatrix *= XMMatrixScaling(0.01f, 0.01f, 0.01f);
			worldMatrix *= XMMatrixRotationY(rotation);
			worldMatrix *= XMMatrixTranslation(1.5f, 0.0f, 0.0f);
			break;

		case 3:
			worldMatrix *= XMMatrixScaling(100.0f, 800.0f, 1.0f);
			worldMatrix *= XMMatrixRotationX(XM_PI / 2.5);
			worldMatrix *= XMMatrixTranslation(0.0f, -10.0f, 120.0f);

			break;
		}

		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
			worldMatrix, viewMatrix, projectionMatrix, m_Models[i]->GetTexture());

		if (!result) return false;
	}


	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::ChangeFilterType(int filterType)
{
	m_TextureShader->ChangeFilterType(m_D3D->GetDevice(), filterType);
}