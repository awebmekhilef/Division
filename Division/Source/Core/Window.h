#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window(const std::string& title, unsigned int width, unsigned int height);
	~Window();

	void Clear() const;
	void Update() const;
	bool IsOpen() const;

private:
	GLFWwindow* m_Window;

	unsigned int m_Width, m_Height;
};
