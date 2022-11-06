#include "Material.h"

Material::Material(Shader* shader)
	: m_Shader(shader)
{
}

void Material::SetInt(const std::string& name, int value)
{
	m_Uniforms[name].Type = ShaderDataType::Int;
	m_Uniforms[name].Int = value;
}

void Material::SetFloat(const std::string& name, float value)
{
	m_Uniforms[name].Type = ShaderDataType::Float;
	m_Uniforms[name].Float = value;
}

void Material::SetVec3(const std::string& name, const glm::vec3& value)
{
	m_Uniforms[name].Type = ShaderDataType::Vec3;
	m_Uniforms[name].Vec3 = value;
}

void Material::SetMat4(const std::string& name, const glm::mat4& value)
{
	m_Uniforms[name].Type = ShaderDataType::Mat4;
	m_Uniforms[name].Mat4 = value;
}

void Material::SetTexture(const std::string& name, Texture* texture, unsigned int unit)
{
	m_UniformSamplers[name].Texture = texture;
	m_UniformSamplers[name].Unit = unit;

	// TODO: Check if cubemap texture
	m_UniformSamplers[name].Type = ShaderDataType::Texture2D;

	m_Shader->Bind();
	m_Shader->UploadInt(name, unit);
}

Shader& Material::GetShader() const
{
	return *m_Shader;
}

const std::map<std::string, UniformValue>& Material::GetUniforms() const
{
	return m_Uniforms;
}

const std::map<std::string, UniformSamplerValue>& Material::GetUniformSamplers() const
{
	return m_UniformSamplers;
}
