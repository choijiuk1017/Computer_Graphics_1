////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	m_rotation.x = 0.0f;
	m_rotation.y = 0.0f;
	m_rotation.z = 0.0f;
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void CameraClass::Render()
{
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Setup the position of the camera in the world.
	position = XMLoadFloat3(&m_position);

	// Setup where the camera is looking by default.
	lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotation.x * 0.0174532925f;
	yaw   = m_rotation.y * 0.0174532925f;
	roll  = m_rotation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}

void CameraClass::MoveForward(float speed)
{
	XMVECTOR forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.x * XM_PI / 180.0f, m_rotation.y * XM_PI / 180.0f, 0.0f);
	forward = XMVector3TransformCoord(forward, rotationMatrix);

	m_position.x += XMVectorGetX(forward) * speed;
	m_position.y += XMVectorGetY(forward) * speed;
	m_position.z += XMVectorGetZ(forward) * speed;
}

void CameraClass::MoveRight(float speed)
{
	XMVECTOR right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, m_rotation.y * XM_PI / 180.0f, 0.0f);
	right = XMVector3TransformCoord(right, rotationMatrix);

	m_position.x += XMVectorGetX(right) * speed;
	m_position.z += XMVectorGetZ(right) * speed;
}

void CameraClass::Rotate(float yawDelta, float pitchDelta)
{
	m_rotation.y += yawDelta;
	m_rotation.x += pitchDelta;

	// pitch 제한 (상하 보는 각도 제한)
	if (m_rotation.x > 89.0f) m_rotation.x = 89.0f;
	if (m_rotation.x < -89.0f) m_rotation.x = -89.0f;
}
