#include "Renderer.h"

#include <glad/glad.h>

#include "../Mesh/Mesh.h"
#include "../Mesh/Model.h"
#include "../Camera/Camera.h"
#include "../Lighting/Light.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"

std::vector<Light*> Renderer::m_Lights;
Shader* Renderer::m_DefaultShader;

void Renderer::Render(Mesh* mesh, Material* material, Camera* camera)
{
	glBindVertexArray(mesh->m_VAO);

	Shader& shader = material->GetShader();

	shader.Bind();

	shader.UploadMat4("uModel", glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f)));
	shader.UploadMat4("uViewProj", camera->GetViewProjectionMatrix());
	shader.UploadVec3("uCameraPos", camera->GetPosition());

	for (auto kv : material->GetUniformSamplers())
	{
		kv.second.Texture->Bind(kv.second.Unit);
	}

	for (auto kv : material->GetUniforms())
	{
		switch (kv.second.Type)
		{
		case ShaderDataType::Int:
			shader.UploadInt(kv.first, kv.second.Int);
			break;
		case ShaderDataType::Float:
			shader.UploadFloat(kv.first, kv.second.Float);
			break;
		case ShaderDataType::Vec3:
			shader.UploadVec3(kv.first, kv.second.Vec3);
			break;
		case ShaderDataType::Mat4:
			shader.UploadMat4(kv.first, kv.second.Mat4);
			break;
		default:
			assert(false);
			break;
		}
	}

	for (int i = 0; i < m_Lights.size(); i++)
	{
		shader.UploadVec3(std::string("uLights[") + std::to_string(i) + "].Position", m_Lights[i]->Position);
		shader.UploadVec3(std::string("uLights[") + std::to_string(i) + "].Ambient", m_Lights[i]->Ambient);
		shader.UploadVec3(std::string("uLights[") + std::to_string(i) + "].Diffuse", m_Lights[i]->Diffuse);
		shader.UploadVec3(std::string("uLights[") + std::to_string(i) + "].Specular", m_Lights[i]->Specular);
	}

	shader.UploadInt("uLightCount", m_Lights.size());

		glDrawArrays(GL_TRIANGLES, 0, static_cast<unsigned int>(mesh->m_Vertices.size()));

	material->GetShader().Unbind();
	glBindVertexArray(0);
}

void Renderer::Render(Model* model, Camera* camera)
{
	for (size_t i = 0; i < model->GetMeshCount(); i++)
	{
		Mesh* mesh = model->GetMeshPair(i).first;
		Material* mat = model->GetMeshPair(i).second;

		Renderer::Render(mesh, mat, camera);
	}
}

void Renderer::AddLight(Light* light)
{
	m_Lights.push_back(light);
}

Shader* Renderer::GetDefaultShader()
{
	if (!m_DefaultShader)
		m_DefaultShader = new Shader("Assets/Shaders/Default.glsl");

	return m_DefaultShader;
}
