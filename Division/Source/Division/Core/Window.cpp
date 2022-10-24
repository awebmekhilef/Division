#include "Window.h"
#include "Input.h"

#include <glad/glad.h>
#include <iostream>
#include <Rendering/Renderer.h>

// TODO: Move to context class
void DebugMessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	std::cout << message << std::endl;
}

Window::Window(const std::string& title, unsigned int width, unsigned int height)
	: m_Width(width), m_Height(height)
{
	if (!glfwInit())
		return;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	m_Window = glfwCreateWindow(m_Width, m_Height, title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glDebugMessageCallback(DebugMessageCallback, nullptr);

	// TODO: These should be initialized in application class
	Input::Init(m_Window);
	Renderer::Init();
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void Window::Close()
{
	glfwSetWindowShouldClose(m_Window, true);
}
