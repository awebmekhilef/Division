#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct GLFWwindow;

class Camera
{
public:
	Camera();
	void SetPerspective(float fov, float aspect, float near, float far);
	
	void UpdateViewMatrix();

	void CusorInput(float xPos, float yPos);
	void ScrollInput(float offset);
	void MouseInput(int button, int action);

	glm::vec3 GetPosition() const;
	glm::mat4 GetViewProjectionMatrix() const;

private:
	void UpdateSphericalPosition();

private:
	glm::vec3 m_Position = glm::vec3(0.0f);
	glm::vec3 m_Rotation = glm::vec3(0.0f);
	glm::vec3 m_Up = glm::vec3(0.0f);

	glm::vec2 m_LastMousePos = glm::vec3(0.0f);

	float m_Radius = 5.0f;
	bool m_Rotating;

	glm::mat4 m_ProjMatrix;
	glm::mat4 m_ViewMatrix;
};