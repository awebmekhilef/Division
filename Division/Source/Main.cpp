#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Division/Mesh/Quad.h"
#include "Division/Mesh/Cube.h"
#include "Division/Camera/Camera.h"
#include "Division/Lighting/Light.h"
#include "Division/Rendering/Texture.h"
#include "Division/Rendering/Shader.h"
#include "Division/Rendering/Renderer.h"
#include "Division/Rendering/Material.h"

#include <stdlib.h>
#include <stdlib.h>
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720

void DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	GLFWwindow* win = glfwCreateWindow(WIDTH, HEIGHT, "Division Engine", NULL, NULL);

	if (!win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(win, KeyCallback);

	glfwMakeContextCurrent(win);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	glDebugMessageCallback(DebugMessageCallback, nullptr);

	Camera camera;
	camera.SetPerspective(45.0f, (float)WIDTH / HEIGHT, 0.1f, 1000.0f);

	Quad quad(-0.5f, 0.5f);
	Cube cube;

	Texture diffuse("Assets/Textures/Container.png");
	Texture specular("Assets/Textures/Container_Specular.png");
	Shader shader("Assets/Shaders/Basic.glsl");

	Material mat(&shader);
	mat.SetTexture("uDiffuse", &diffuse, 0);
	mat.SetTexture("uSpecular", &specular, 1);
	mat.SetFloat("uShininess", 64.0f);

	Light light1 = {
		{ 0.0f, 2.0f, 3.0f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.7f, 0.7f, 0.7f },
		{ 1.0f, 1.0f, 1.0f }
	};

	Light light2 = {
		{ 0.0f, 2.0f, -3.0f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.7f, 0.0f, 0.7f },
		{ 1.0f, 1.0f, 0.0f }
	};

	Light light3 = {
		{ 3.0f, 2.0f, 0.0f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.0f, 0.0f, 0.7f },
		{ 0.0f, 1.0f, 1.0f }
	};

	Light light4 = {
		{ 3.0f, 2.0f, 0.0f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.0f, 0.7f, 0.0f },
		{ 1.0f, 0.0f, 1.0f }
	};

	Renderer::AddLight(&light1);
	Renderer::AddLight(&light2);
	Renderer::AddLight(&light3);
	Renderer::AddLight(&light3);

	while (!glfwWindowShouldClose(win))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.ProcessInput(win, 0.0f);
		camera.UpdateViewMatrix();

		Renderer::Render(&cube, &mat, &camera);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
}

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

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
