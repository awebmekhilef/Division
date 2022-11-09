#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <iostream>

#include <algorithm>

const float PI = 3.142f;

Camera::Camera()
{
	UpdateSphericalPosition();
}

void Camera::SetPerspective(float fov, float aspect, float near, float far)
{
	m_ProjMatrix = glm::perspective(fov, aspect, near, far);
}

void Camera::UpdateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::UpdateSphericalPosition()
{
	m_Position.x = m_Radius * -sinf(m_Rotation.x * (PI / 180)) * cosf((m_Rotation.y) * (PI / 180));
	m_Position.y = m_Radius * -sinf((m_Rotation.y) * (PI / 180));
	m_Position.z = -m_Radius * cosf((m_Rotation.x) * (PI / 180)) * cosf((m_Rotation.y) * (PI / 180));
}

void Camera::ScrollInput(float offset)
{
	m_Radius -= 0.5f * offset;
	UpdateSphericalPosition();
}

void Camera::CusorInput(float xPos, float yPos)
{
	const float sensitivity = 0.2f;

	float xOff = m_LastMousePos.x - xPos;
	float yOff = m_LastMousePos.y - yPos;

	if (m_Rotating)
	{
		if (xOff != 0.0f || yOff != 0.0f)
		{
			m_Rotation.x += xOff * sensitivity;
			m_Rotation.y += yOff * sensitivity;

			UpdateSphericalPosition();
		}
	}

	m_LastMousePos = glm::vec2(xPos, yPos);
}

void Camera::MouseInput(int button, int action)
{
	if (button == GLFW_MOUSE_BUTTON_1)
		m_Rotating = action == GLFW_PRESS;
}

glm::vec3 Camera::GetPosition() const
{
	return m_Position;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return m_ProjMatrix;
}
