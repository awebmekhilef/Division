#include "Core/Window.h"
#include "Core/Rendering/Buffer.h"
#include "Core/Rendering/VertexArray.h"
#include "Core/Rendering/BufferLayout.h"
#include "Core/Rendering/Shader.h"
#include "Core/Rendering/Texture.h"

#include <glad/glad.h>

std::string vSrc =
R"(
#version 430 core

layout(location=0) in vec2 aPosition;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoords;

out vec3 vColor;
out vec2 vTexCoords;

void main()
{
	gl_Position = vec4(aPosition, 0.0, 1.0);

	vColor = aColor;
	vTexCoords = aTexCoords;
}
)";

std::string fSrc =
R"(
#version 430 core

in vec3 vColor;
in vec2 vTexCoords;

out vec4 Color;

uniform sampler2D uTexture;

void main() 
{
	Color = texture(uTexture, vTexCoords) * vec4(vColor, 1.0);
}
)";

int main()
{
	Window win("Division Engine", 1280, 720);

	float vertices[] = {
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	BufferLayout layout;
	layout.Push(2, GL_FLOAT, false);
	layout.Push(3, GL_FLOAT, false);
	layout.Push(2, GL_FLOAT, false);

	VertexArray va;

	VertexBuffer vb(vertices, sizeof(vertices));
	IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

	va.AddBuffer(vb, layout);

	Shader shader(vSrc, fSrc);

	Texture texture("Assets/Textures/Checkerboard.png");
	texture.Bind();

	while (win.IsOpen())
	{
		win.Clear();

		// TODO: Move to renderer once create shader
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

		win.Update();
	}
}
