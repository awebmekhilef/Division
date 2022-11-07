#include "Camera.h"

#include <GLFW/glfw3.h>
#include <iostream>

void Camera::SetPerspective(float fov, float aspect, float near, float far)
{
	m_ProjMatrix = glm::perspective(fov, aspect, near, far);
}

void Camera::UpdateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::ProcessInput(GLFWwindow* win, float dt)
{
	const float radius = 5.0f;

	m_Position.x = sin(glfwGetTime()) * radius;
	m_Position.z = cos(glfwGetTime()) * radius;
	m_Position.y = 2.0f;
}

glm::mat4 Camera::GetViewProjectionMatrix() const
{
	return m_ProjMatrix * m_ViewMatrix;
}
