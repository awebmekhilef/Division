#pragma once

#include "glm/glm.hpp"

#include <string>

class Shader
{
public:
	Shader(const std::string& vertSrc, const std::string& fragSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetFloat(const std::string& name, float value);
	void SetFloat3(const std::string& name, const glm::vec3& value);
	void SetMat4(const std::string& name, const glm::mat4& value);

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);

private:
	unsigned int m_RendererID;
};
