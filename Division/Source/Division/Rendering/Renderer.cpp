#include "Renderer.h"

#include <glad/glad.h>

#include "../Mesh/Mesh.h"
#include "Shader.h"

void Renderer::Render(Mesh* mesh, Shader* shader)
{
	glBindVertexArray(mesh->m_VAO);
	shader->Bind();

	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->m_Indices.size()), GL_UNSIGNED_INT, nullptr);

	shader->Unbind();
	glBindVertexArray(0);
}
