#include "Renderer.h"

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader)
{
	va.Bind();
	shader.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}