#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Division/Mesh/Cube.h"
#include "Division/Mesh/Model.h"
#include "Division/Camera/Camera.h"
#include "Division/Lighting/Light.h"
#include "Division/Rendering/Shader.h"
#include "Division/Rendering/Renderer.h"
#include "Division/Rendering/TextureCube.h"

#include <stdlib.h>
#include <stdlib.h>
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720

void DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

void DrawMetricsWindow();
void DrawPropertiesWindow(std::vector<Model*> models, std::vector<Light*> lights);

// Global so it can be accessed in GLFW callbacks
Camera camera;

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
	glfwSetFramebufferSizeCallback(win, FrameBufferSizeCallback);
	glfwSetScrollCallback(win, ScrollCallback);
	glfwSetCursorPosCallback(win, CursorPosCallback);
	glfwSetMouseButtonCallback(win, MouseButtonCallback);

	glfwMakeContextCurrent(win);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

	ImGui_ImplGlfw_InitForOpenGL(win, true);
	ImGui_ImplOpenGL3_Init("#version 430 core");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	glClearColor(0.53f, 0.8f, 0.92f, 1.0f);

	glDebugMessageCallback(DebugMessageCallback, nullptr);

	Renderer::Init();

	camera.SetPerspective(45.0f, (float)WIDTH / HEIGHT, 0.1f, 1000.0f);

	/* ========= MODELS ========= */

	std::vector<Model*> models = {
		new Model("Assets/Models/cyborg/cyborg.obj"),
		new Model("Assets/Models/backpack/backpack.obj")
	};

	models[0]->SetPosition({ 0.0f, 0.0f, 0.0f });
	models[0]->SetRotation({ 45.0f, 180.0f, 0.0f });
	models[1]->SetScale({ 0.5f, 0.5f, 0.5f });
	// models[0]->AddChild(models[1]);

	/* ========= LIGHTS ========= */

	std::vector<Light*> lights;

	Light* light1 = new Light{
		{ 0.0f, 1.5f, 3.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }
	};

	Light* light2 = new Light{
		{ 0.0f, 1.5f, -3.0f },
		{ 1.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }
	};

	Light* light3 = new Light{
		{ -3.0f, 1.5f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }
	};

	Light* light4 = new Light{
		{ 3.0f, 1.5f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }
	};

	lights.push_back(light1);
	lights.push_back(light2);
	lights.push_back(light3);
	lights.push_back(light4);

	Renderer::AddLight(lights[0]);
	Renderer::AddLight(lights[1]);
	Renderer::AddLight(lights[2]);
	Renderer::AddLight(lights[3]);

	/* ========= SKYBOX ========= */

	Cube skyboxCube;
	TextureCube skyboxTexture("Assets/Textures/Skybox/");
	Material skyboxMaterial(new Shader("Assets/Shaders/Skybox.glsl"));

	skyboxMaterial.SetTextureCube("uSkybox", &skyboxTexture);

	while (!glfwWindowShouldClose(win))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.UpdateViewMatrix();

		Renderer::RenderSkybox(&skyboxCube, &skyboxMaterial, &camera); 

		for (auto* model : models)
			Renderer::Render(model, &camera);

		for (auto light : lights)
			Renderer::RenderLight(light, &camera);

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		DrawMetricsWindow();
		DrawPropertiesWindow(models, lights);

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

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (!ImGui::GetIO().WantCaptureMouse)
		camera.MouseInput(button, action);
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.ScrollInput(yOffset);
}

void CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
	camera.CusorInput(xPos, yPos);
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	camera.SetPerspective(45.0f, (float)width / height, 0.1f, 1000.0f);
}

void DrawMetricsWindow()
{
	ImGui::Begin("Metrics");
	ImGui::Text("IMGUI Version: %s", ImGui::GetVersion());
	ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("%d visible windows, %d active allocations", ImGui::GetIO().MetricsRenderWindows, ImGui::GetIO().MetricsActiveAllocations);
	ImGui::End();
}

void DrawPropertiesWindow(std::vector<Model*> models, std::vector<Light*> lights)
{
	ImGui::Begin("Entity hierarchy");

	for (int i = 0; i < models.size(); i++)
		models[i]->DrawDebugGui(i);

	for (int i = 0; i < lights.size(); i++)
	{
		Light* light = lights[i];

		// little hack..
		ImGui::PushID(light);

		if (ImGui::CollapsingHeader(("Light #" + std::to_string(i)).c_str()))
		{
			ImGui::ColorEdit3("Color", glm::value_ptr(light->Diffuse));
			ImGui::ColorEdit3("Specular", glm::value_ptr(light->Specular));
			ImGui::DragFloat3("Position", glm::value_ptr(light->Position), 0.25f);
		}

		ImGui::PopID();
	}

	ImGui::End();
}