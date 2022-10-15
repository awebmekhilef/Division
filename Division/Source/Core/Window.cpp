#include "Window.h"

#include <glad/glad.h>

Window::Window(const std::string& title, unsigned int width, unsigned int height)
	: m_Width(width), m_Height(height)
{
	if (!glfwInit())
		return;

	// TODO: Hints

	m_Window = glfwCreateWindow(m_Width, m_Height, title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Update() const
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

bool Window::IsOpen() const
{
	return !glfwWindowShouldClose(m_Window);
}
