#include "Renderer.h"

#include <glad/glad.h>

#include "../Mesh/Mesh.h"
#include "Material.h"
#include "Texture.h"

void Renderer::Render(Mesh* mesh, Material* material)
{
	glBindVertexArray(mesh->m_VAO);

	material->GetShader().Bind();

	// TODO: Set MVP and camera pos

	for (auto kv : material->GetUniformSamplers())
	{
		kv.second.Texture->Bind(kv.second.Unit);
	}

	for (auto kv : material->GetUniforms())
	{
		switch (kv.second.Type)
		{
		case ShaderDataType::Int:
			material->GetShader().UploadInt(kv.first, kv.second.Int);
			break;
		case ShaderDataType::Mat4:
			material->GetShader().UploadMat4(kv.first, kv.second.Mat4);
			break;
		default:
			assert(false);
			break;
		}
	}

	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->m_Indices.size()), GL_UNSIGNED_INT, nullptr);

	material->GetShader().Unbind();
	glBindVertexArray(0);
}
