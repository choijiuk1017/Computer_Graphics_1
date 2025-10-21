////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_Light = 0;

	m_Light1 = 0;
	m_Light2 = 0;
	m_Light3 = 0;
	m_Light4 = 0;

	intensity = 1.0f;
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
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube
//	m_Camera->SetPosition(0.0f, 0.5f, -3.0f);	// for chair
	for (int i = 0; i < 4; i++)
	{
		ModelClass* model = new ModelClass;

		m_Models.push_back(model);
	}

	// Create the model object.
	if (!m_Models[0])
	{
		return false;
	}
	result = m_Models[0]->Initialize(m_D3D->GetDevice(), L"./data/Sword.obj", L"./data/Sword.dds");
	if (!result)
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
	result = m_Models[3]->Initialize(m_D3D->GetDevice(), L"./data/plane01.txt", L"./data/Ground.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetPosition(0.0f, 0.0f, 0.0f);
	//m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	//m_Light->SetDirection(1.0f, -2.0f, 0.0f);
	m_Light->SetDirection(1.0f, 0.0f, 0.0f);
	//m_Light->SetDirection(1.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the light object.
	m_Light1 = new LightClass;
	if (!m_Light1)
	{
		return false;
	}

	// Initialize the first light object.
	m_Light1->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_Light1->SetPosition(3.0f, 1.0f, -0.0f);

	// Create the second light object.
	m_Light2 = new LightClass;
	if (!m_Light2)
	{
		return false;
	}

	// Initialize the second light object.
	m_Light2->SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_Light2->SetPosition(-3.0f, 1.0f, 0.0f);

	// Create the third light object.
	m_Light3 = new LightClass;
	if (!m_Light3)
	{
		return false;
	}

	// Initialize the third light object.
	m_Light3->SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
	m_Light3->SetPosition(0.0f, 1.0f, 0.0f);

	// Create the fourth light object.
	m_Light4 = new LightClass;
	if (!m_Light4)
	{
		return false;
	}

	// Initialize the fourth light object.
	m_Light4->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light4->SetPosition(0.0f, 0.0f, 0.0f);

	specularColor[0] = m_Light1->GetDiffuseColor();
	specularColor[1] = m_Light2->GetDiffuseColor();
	specularColor[2] = m_Light3->GetDiffuseColor();
	specularColor[3] = m_Light4->GetDiffuseColor();

	return true;
}


void GraphicsClass::Shutdown()
{
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

	if (m_Light1)
	{
		delete m_Light1;
		m_Light1 = 0;
	}

	if (m_Light2)
	{
		delete m_Light2;
		m_Light2 = 0;
	}

	if (m_Light3)
	{
		delete m_Light3;
		m_Light3 = 0;
	}

	if (m_Light4)
	{
		delete m_Light4;
		m_Light4 = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}


	
	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;
	m_Camera->SetPosition(0.0f, 2.0f, -12.0f);

	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
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
	XMFLOAT4 diffuseColor[4];
	XMFLOAT4 lightPosition[4];
	bool result;
	
	// Create the diffuse color array from the four light colors.
	diffuseColor[0] = m_Light1->GetDiffuseColor();
	diffuseColor[1] = m_Light2->GetDiffuseColor();
	diffuseColor[2] = m_Light3->GetDiffuseColor();
	diffuseColor[3] = m_Light4->GetDiffuseColor();

	for (int i = 0; i < 3; i++)
	{
		diffuseColor[i].x = diffuseColor[i].x * intensity;
		diffuseColor[i].y = diffuseColor[i].y * intensity;
		diffuseColor[i].z = diffuseColor[i].z * intensity;
		diffuseColor[i].w = 1.0f;
	}

	// Create the light position array from the four light positions.
	lightPosition[0] = m_Light1->GetPosition();
	lightPosition[1] = m_Light2->GetPosition();
	lightPosition[2] = m_Light3->GetPosition();
	lightPosition[3] = m_Light4->GetPosition();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	worldMatrix = XMMatrixRotationY(rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
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
			worldMatrix *= XMMatrixTranslation(3.0f, 0.0f, 0.0f);
			break;
		case 1:
			worldMatrix *= XMMatrixScaling(0.01f, 0.01f, 0.01f);
			worldMatrix *= XMMatrixRotationY(rotation);
			worldMatrix *= XMMatrixTranslation(-3.0f, 1.0f, 1.0f);
			break;
		case 2:
			worldMatrix *= XMMatrixScaling(0.01f, 0.01f, 0.01f);
			worldMatrix *= XMMatrixRotationY(rotation);
			worldMatrix *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);
			break;
		}
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
			worldMatrix, viewMatrix, projectionMatrix,
			m_Models[i]->GetTexture(),
			m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor() /*specularColor[i]*/, m_Light->GetSpecularPower(), diffuseColor, lightPosition);

		if (!result) return false;
	}


	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::IncreaseIntensity()
{
	intensity += 0.05f;
}

void GraphicsClass::DecreaseIntensity()
{
	intensity -= 0.05f;
}

void GraphicsClass::SetAmbient(int typeNum)
{
	if (typeNum == 0)
	{
		m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	}
}

void GraphicsClass::SetDiffuse(int typeNum)
{
	if (typeNum == 0)
	{
		m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_Light1->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_Light2->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_Light3->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_Light4->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light1->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
		m_Light2->SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);
		m_Light3->SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
		m_Light4->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}


void GraphicsClass::SetSpecular(int typeNum)
{
	if (typeNum == 0)
	{
		m_Light->SetSpecularPower(100000.f);
	}
	else
	{
		m_Light->SetSpecularPower(32.0f);
	}
}