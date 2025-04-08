////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_ColorShader = 0;
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
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	// Create the model object.
	for (int i = 0; i < 3; ++i)
	{
		ModelClass* model = new ModelClass;
		if (!model)
			return false;

		result = model->Initialize(m_D3D->GetDevice(), i);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize a model object.", L"Error", MB_OK);
			return false;
		}

		m_Models.push_back(model);
	}

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
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
	m_Models.clear();

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


	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{
	XMMATRIX viewMatrix, projectionMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	
	m_D3D->GetProjectionMatrix(projectionMatrix);

	for (int i = 0; i < m_Models.size(); i++)
	{
		XMMATRIX worldMatrix = m_Models[i]->GetWorldMatrix();
		m_D3D->GetWorldMatrix(worldMatrix);

		m_Models[i]->Render(m_D3D->GetDeviceContext());

		worldMatrix *= XMMatrixScaling(0.5f, 0.5f, 0.5f);

		switch (i)
		{
		case 0:
			worldMatrix *= XMMatrixRotationY(180.0f / XM_PI - rotation);
			worldMatrix *= XMMatrixTranslation(-4.0f, 0.0f, 0.0f);
			break;
		
		case 1:
			worldMatrix *= XMMatrixRotationZ(180.0f / XM_PI - rotation);
			worldMatrix *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);
			break;

		case 2:
			worldMatrix *= XMMatrixRotationX(180.0f / XM_PI - rotation);
			worldMatrix *= XMMatrixTranslation(4.0f, 0.0f, 0.0f);
			break;
		}

		result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
			worldMatrix, viewMatrix, projectionMatrix);

		if (!result) return false;
	}
	
	
	rotation += 0.1f;

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
} 