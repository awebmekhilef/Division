#include "Divison.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main()
{
	Window win("Division Engine", 1280, 720);

	float vertices[] = {
		-0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Top left
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Bottom left
		 0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom right
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	BufferLayout layout;
	layout.Push(2, GL_FLOAT, false);
	layout.Push(3, GL_FLOAT, false);
	layout.Push(2, GL_FLOAT, false);

	VertexArray va;

	VertexBuffer vb(vertices, sizeof(vertices));
	IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

	va.AddBuffer(vb, layout);

	Shader shader("Assets/Shaders/Sprite.glsl");

	Texture texture("Assets/Textures/Checkerboard.png");
	texture.Bind();

	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 proj = glm::perspective(
		glm::radians(45.0f),
		(float)win.GetWidth() / win.GetHeight(),
		0.1f, 1000.0f);

	float lastFrameTime = 0.0f;

	glm::vec3 pos(0.0f);
	float rotation = 0.0f;

	while (win.IsOpen())
	{
		win.Clear();

		float time = Time::GetTime();
		float dt = time - lastFrameTime;
		lastFrameTime = time;

		if (Input::IsKeyHeld(GLFW_KEY_A))
			pos.x -= 5.0f * dt;
		else if (Input::IsKeyHeld(GLFW_KEY_D))
			pos.x += 5.0f * dt;
		if (Input::IsKeyHeld(GLFW_KEY_W))
			pos.y += 5.0f * dt;
		else if (Input::IsKeyHeld(GLFW_KEY_S))
			pos.y -= 5.0f * dt;

		if (Input::IsKeyHeld(GLFW_KEY_ESCAPE))
			win.Close();

		rotation += 45.0f * dt;

		glm::mat4 model(1.0f);
		model = glm::translate(model, pos);
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 mvp = proj * view * model;
		shader.SetMat4("uMVP", mvp);

		Renderer::Draw(va, ib, shader);

		win.Update();
	}
}