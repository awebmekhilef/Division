#include "Renderer.h"

#include <glad/glad.h>

#include "../Mesh/Mesh.h"
#include "../Mesh/Cube.h"
#include "../Mesh/Model.h"
#include "../Camera/Camera.h"
#include "../Lighting/Light.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"

std::vector<Light*> Renderer::m_Lights;

Shader* Renderer::m_DefaultShader;
Material* Renderer::m_DebugLightMaterial;
Cube* Renderer::m_DebugLightMesh;

void Renderer::Init()
{
	m_DefaultShader = new Shader("Assets/Shaders/Default.glsl");
	m_DebugLightMesh = new Cube();

	m_DebugLightMaterial = new Material(new Shader("Assets/Shaders/Light.glsl"));
}

void Renderer::Render(Mesh* mesh, Material* material, Camera* camera, const glm::mat4& transform)
{
	glBindVertexArray(mesh->m_VAO);

	Shader& shader = material->GetShader();

	shader.Bind();

	shader.UploadMat4("uModel", transform);
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
		shader.UploadVec3(std::string("uLights[") + std::to_string(i) + "].Diffuse", m_Lights[i]->Diffuse);
		shader.UploadVec3(std::string("uLights[") + std::to_string(i) + "].Specular", m_Lights[i]->Specular);
	}

	shader.UploadInt("uLightCount", m_Lights.size());

	if (mesh->m_Indices.size() > 0)
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->m_Indices.size()), GL_UNSIGNED_INT, nullptr);
	else
		glDrawArrays(GL_TRIANGLES, 0, static_cast<unsigned int>(mesh->m_Vertices.size()));

	shader.Unbind();
	glBindVertexArray(0);
}

void Renderer::Render(Model* model, Camera* camera)
{
	for (size_t i = 0; i < model->GetMeshCount(); i++)
	{
		Mesh* mesh = model->GetMeshPair(i).first;
		Material* mat = model->GetMeshPair(i).second;

		Renderer::Render(mesh, mat, camera, model->GetTransform());
	}
}

void Renderer::RenderLight(Light* light, Camera* camera)
{
	glm::mat4 transform = glm::identity<glm::mat4>();
	transform = glm::translate(transform, light->Position);
	transform = glm::scale(transform, glm::vec3(0.25f));

	m_DebugLightMaterial->SetVec3("uDiffuseColor", light->Diffuse);

	Render(m_DebugLightMesh, m_DebugLightMaterial, camera, transform);
}

void Renderer::AddLight(Light* light)
{
	m_Lights.push_back(light);
}

Shader* Renderer::GetDefaultShader()
{
	return m_DefaultShader;
}
