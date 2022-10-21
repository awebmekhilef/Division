#pragma once

#define GLFW_INCLUDE_NONE
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

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

private:
	GLFWwindow* m_Window;

	unsigned int m_Width, m_Height;
};
