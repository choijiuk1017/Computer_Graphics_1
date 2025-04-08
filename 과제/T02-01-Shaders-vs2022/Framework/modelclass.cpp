////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"


ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device, int shapeType)
{
	bool result;

	m_shapeType = shapeType;
	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelClass::Shutdown()
{
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	if (m_shapeType == 0 || m_shapeType == 1)
	{
		// 검, 도끼 모양 용
		m_vertexCount = 11;

		m_indexCount = 21;
	}
	else if (m_shapeType == 2)
	{
		// 창 모양 용
		m_vertexCount = 7;

		m_indexCount = 15;
	}
	
	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	XMFLOAT4 gray = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	XMFLOAT4 brown = XMFLOAT4(0.6f, 0.3f, 0.1f, 1.0f);
	XMFLOAT4 white = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	if (m_shapeType == 0)
	{
		// 검 모양 다각형
		// Load the vertex array with data.
		vertices[0].position = XMFLOAT3(-1.0f, 3.0f, 0.0f);  // Bottom left.
		vertices[0].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[1].position = XMFLOAT3(0.0f, 4.0f, 0.0f);  // Top middle.
		vertices[1].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[2].position = XMFLOAT3(1.0f, 3.0f, 0.0f);  // Bottom right.
		vertices[2].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[3].position = XMFLOAT3(-1.0f, 0.0f, 0.0f);  // Bottom right.
		vertices[3].color = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

		vertices[4].position = XMFLOAT3(-0.3f, 0.0f, 0.0f);  // Bottom right.
		vertices[4].color = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

		vertices[5].position = XMFLOAT3(0.3f, 0.0f, 0.0f);  // Bottom right.
		vertices[5].color = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

		vertices[6].position = XMFLOAT3(1.0f, 0.0f, 0.0f);  // Bottom right.
		vertices[6].color = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

		vertices[7].position = XMFLOAT3(-1.5f, -1.0f, 0.0f);  // Bottom right.
		vertices[7].color = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

		vertices[8].position = XMFLOAT3(1.5f, -1.0f, 0.0f);  // Bottom right.
		vertices[8].color = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

		vertices[9].position = XMFLOAT3(-0.3f, -2.0f, 0.0f);  // Bottom right.
		vertices[9].color = XMFLOAT4(0.6f, 0.3f, 0.1f, 1.0f);

		vertices[10].position = XMFLOAT3(0.3f, -2.0f, 0.0f);  // Bottom right.
		vertices[10].color = XMFLOAT4(0.6f, 0.3f, 0.1f, 1.0f);

		indices[0] = 0;  // Bottom left.
		indices[1] = 1;  // Top middle.
		indices[2] = 2;  // Bottom right.

		indices[3] = 3;  // Bottom left.
		indices[4] = 0;  // Top middle.
		indices[5] = 6;  // Bottom right.

		indices[6] = 0;  // Bottom left.
		indices[7] = 2;  // Top middle.
		indices[8] = 6;  // Bottom right.

		indices[9] = 3;  // Bottom left.
		indices[10] = 6;  // Top middle.
		indices[11] = 7;  // Bottom right.

		indices[12] = 3;  // Bottom left.
		indices[13] = 6;  // Top middle.
		indices[14] = 8;  // Bottom right.

		indices[15] = 4;  // Bottom left.
		indices[16] = 5;  // Top middle.
		indices[17] = 10;  // Bottom right.

		indices[18] = 9;  // Bottom left.
		indices[19] = 4;  // Top middle.
		indices[20] = 10;  // Bottom right.
	}
	else if (m_shapeType == 1)
	{
		vertices[0].position = XMFLOAT3(0.0f, 4.0f, 0.0f);  // Bottom left.
		vertices[0].color = brown;

		vertices[1].position = XMFLOAT3(-0.3f, 3.0f, 0.0f);  // Top middle.
		vertices[1].color = brown;

		vertices[2].position = XMFLOAT3(0.3f, 3.0f, 0.0f);  // Bottom right.
		vertices[2].color = brown;

		vertices[3].position = XMFLOAT3(-2.0f, 4.0f, 0.0f);  // Bottom right.
		vertices[3].color = white;

		vertices[4].position = XMFLOAT3(2.0f, 4.0f, 0.0f);  // Bottom right.
		vertices[4].color = white;

		vertices[5].position = XMFLOAT3(-2.0f, 2.0f, 0.0f);  // Bottom right.
		vertices[5].color = white;

		vertices[6].position = XMFLOAT3(-0.3f, 2.3f, 0.0f);  // Bottom right.
		vertices[6].color = gray;

		vertices[7].position = XMFLOAT3(0.3f, 2.3f, 0.0f);  // Bottom right.
		vertices[7].color = gray;

		vertices[8].position = XMFLOAT3(2.0f, 2.0f, 0.0f);  // Bottom right.
		vertices[8].color = white;

		vertices[9].position = XMFLOAT3(-0.3f, 0.0f, 0.0f);  // Bottom right.
		vertices[9].color = brown;

		vertices[10].position = XMFLOAT3(0.3f, 0.0f, 0.0f);  // Bottom right.
		vertices[10].color = brown;

		indices[0] = 1;  // Bottom left.
		indices[1] = 0;  // Top middle.
		indices[2] = 2;  // Bottom right.

		indices[3] = 9;  // Bottom left.
		indices[4] = 1;  // Top middle.
		indices[5] = 10;  // Bottom right.

		indices[6] = 10;  // Bottom left.
		indices[7] = 1;  // Top middle.
		indices[8] = 2;  // Bottom right.

		indices[9] = 6;  // Bottom left.
		indices[10] = 3;  // Top middle.
		indices[11] = 1;  // Bottom right.

		indices[12] = 6;  // Bottom left.
		indices[13] = 5;  // Top middle.
		indices[14] = 3;  // Bottom right.

		indices[15] = 7;  // Bottom left.
		indices[16] = 2;  // Top middle.
		indices[17] = 4;  // Bottom right.

		indices[18] = 8;  // Bottom left.
		indices[19] = 7;  // Top middle.
		indices[20] = 4;  // Bottom right.

	}
	else if(m_shapeType == 2)
	{
		vertices[0].position = XMFLOAT3(0.0f, 4.0f, 0.0f);  // Bottom left.
		vertices[0].color = white;

		vertices[1].position = XMFLOAT3(-0.5f, 2.3f, 0.0f);  // Top middle.
		vertices[1].color = white;

		vertices[2].position = XMFLOAT3(0.5f, 2.3f, 0.0f);  // Bottom right.
		vertices[2].color = white;

		vertices[3].position = XMFLOAT3(-0.3f, 2.0f, 0.0f);  // Bottom right.
		vertices[3].color = brown;

		vertices[4].position = XMFLOAT3(0.3f, 2.0f, 0.0f);  // Bottom right.
		vertices[4].color = brown;

		vertices[5].position = XMFLOAT3(-0.3f, -2.0f, 0.0f);  // Bottom right.
		vertices[5].color = brown;

		vertices[6].position = XMFLOAT3(0.3f, -2.0f, 0.0f);  // Bottom right.
		vertices[6].color = brown;


		indices[0] = 1;  // Bottom left.
		indices[1] = 0;  // Top middle.
		indices[2] = 2;  // Bottom right.

		indices[3] = 3;  // Bottom left.
		indices[4] = 1;  // Top middle.
		indices[5] = 2;  // Bottom right.

		indices[6] = 3;  // Bottom left.
		indices[7] = 2;  // Top middle.
		indices[8] = 4;  // Bottom right.

		indices[9] = 5;  // Bottom left.
		indices[10] = 3;  // Top middle.
		indices[11] = 4;  // Bottom right.

		indices[12] = 5;  // Bottom left.
		indices[13] = 4;  // Top middle.
		indices[14] = 6;  // Bottom right.
	}

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

// This sets the vertex buffer and index buffer as active on the input assembler in the GPU. 
// Once the GPU has an active vertex buffer, it can then use the shader to render that buffer. 
// This function also defines how those buffers should be drawn such as triangles, lines, fans, 
// and etc using the IASetPrimitiveTopology DirectX function.
void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}