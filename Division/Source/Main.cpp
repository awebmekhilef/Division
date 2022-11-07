#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Division/Mesh/Model.h"
#include "Division/Camera/Camera.h"
#include "Division/Lighting/Light.h"
#include "Division/Rendering/Shader.h"
#include "Division/Rendering/Renderer.h"


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
	glfwWindowHint(GLFW_SAMPLES, 4);

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

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(win, true);
	ImGui_ImplOpenGL3_Init("#version 430 core");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	glClearColor(0.53f, 0.8f, 0.92f, 1.0f);

	glDebugMessageCallback(DebugMessageCallback, nullptr);

	Camera camera;
	camera.SetPerspective(45.0f, (float)WIDTH / HEIGHT, 0.1f, 1000.0f);

	Model model1("Assets/Models/cyborg/cyborg.obj");
	Model model2("Assets/Models/backpack/backpack.obj");

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

		Renderer::Render(&model1, &camera);
		Renderer::Render(&model2, &camera);

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowMetricsWindow();

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
