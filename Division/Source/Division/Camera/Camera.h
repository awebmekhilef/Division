#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct GLFWwindow;

// TODO: Abstract this out to subclass from fly and rotation camera
class Camera
{
public:
	void SetPerspective(float fov, float aspect, float near, float far);

	void UpdateViewMatrix();
	void ProcessInput(GLFWwindow* win, float dt);

	glm::vec3 GetPosition() const { return m_Position; }

	glm::mat4 GetViewProjectionMatrix() const;

private:
	glm::vec3 m_Position = glm::vec3(0.0f);

	glm::mat4 m_ProjMatrix;
	glm::mat4 m_ViewMatrix;
};