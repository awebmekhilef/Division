#pragma once

#include "Shader.h"
#include "ShaderTypes.h"

#include <map>
#include <string>

class Material
{
public:
	Material(Shader* shader);

	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void SetVec3(const std::string& name, const glm::vec3& value);
	void SetMat4(const std::string& name, const glm::mat4& value);

	void SetTexture(const std::string& name, Texture* texture, unsigned int unit = 0);
	void SetTextureCube(const std::string& name, TextureCube* texture, unsigned int unit = 0);

	Shader& GetShader() const;

	const std::map<std::string, UniformValue>& GetUniforms() const;
	const std::map<std::string, UniformSamplerValue>& GetUniformSamplers() const;

private:
	Shader* m_Shader;

	std::map<std::string, UniformValue> m_Uniforms;
	std::map<std::string, UniformSamplerValue> m_UniformSamplers;
};
