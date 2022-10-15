#include "Core/Window.h"
#include "Core/Rendering/Buffer.h"

#include <glad/glad.h>

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

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	VertexBuffer vb(vertices, sizeof(vertices));
	IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	while (win.IsOpen())
	{
		win.Clear();

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

		win.Update();
	}
}
