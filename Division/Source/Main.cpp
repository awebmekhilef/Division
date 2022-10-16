#include "Core/Window.h"
#include "Core/Rendering/Buffer.h"
#include "Core/Rendering/VertexArray.h"
#include "Core/Rendering/BufferLayout.h"
#include "Core/Rendering/Shader.h"

#include <glad/glad.h>

std::string vSrc =
R"(
#version 430 core

layout(location=0) in vec2 aPosition;

void main()
{
	gl_Position = vec4(aPosition, 0.0, 1.0);
}
)";

std::string fSrc =
R"(
#version 430 core

out vec4 Color;

void main() 
{
	Color = vec4(1.0, 0.0, 1.0, 1.0);
}
)";

int main()
{
	Window win("Division Engine", 1280, 720);

	float vertices[] = {
		-0.5f, -0.5f,
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	BufferLayout layout;
	layout.Push(2, GL_FLOAT, false);

	VertexArray va;

	VertexBuffer vb(vertices, sizeof(vertices));
	IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

	va.AddBuffer(vb, layout);

	Shader shader(vSrc, fSrc);

	while (win.IsOpen())
	{
		win.Clear();

		// TODO: Move to renderer once create shader
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

		win.Update();
	}
}
