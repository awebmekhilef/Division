#include "Renderer.h"

#include <glad/glad.h>

#include "../Mesh/Mesh.h"
#include "../Camera/Camera.h"
#include "../Lighting/Light.h"
#include "Material.h"
#include "Texture.h"

std::vector<Light*> Renderer::m_Lights;

void Renderer::Render(Mesh* mesh, Material* material, Camera* camera)
{
	glBindVertexArray(mesh->m_VAO);

	material->GetShader().Bind();

	material->GetShader().UploadMat4("uModel", glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f)));
	material->GetShader().UploadMat4("uViewProj", camera->GetViewProjectionMatrix());
	material->GetShader().UploadVec3("uCameraPos", camera->GetPosition());

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
		case ShaderDataType::Float:
			material->GetShader().UploadFloat(kv.first, kv.second.Float);
			break;
		case ShaderDataType::Vec3:
			material->GetShader().UploadVec3(kv.first, kv.second.Vec3);
			break;
		case ShaderDataType::Mat4:
			material->GetShader().UploadMat4(kv.first, kv.second.Mat4);
			break;
		default:
			assert(false);
			break;
		}
	}

	for (int i = 0; i < m_Lights.size(); i++)
	{
		material->GetShader().UploadVec3(std::string("uLights[") + std::to_string(i) + "].Position", m_Lights[i]->Position);
		material->GetShader().UploadVec3(std::string("uLights[") + std::to_string(i) + "].Ambient", m_Lights[i]->Ambient);
		material->GetShader().UploadVec3(std::string("uLights[") + std::to_string(i) + "].Diffuse", m_Lights[i]->Diffuse);
		material->GetShader().UploadVec3(std::string("uLights[") + std::to_string(i) + "].Specular", m_Lights[i]->Specular);
	}

	material->GetShader().UploadInt("uLightCount", m_Lights.size());

	if (mesh->m_Indices.size() > 0)
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->m_Indices.size()), GL_UNSIGNED_INT, nullptr);
	else
		glDrawArrays(GL_TRIANGLES, 0, static_cast<unsigned int>(mesh->m_Vertices.size()));

	material->GetShader().Unbind();
	glBindVertexArray(0);
}

void Renderer::AddLight(Light* light)
{
	m_Lights.push_back(light);
}
