#pragma once

#include <glm/glm.hpp>

#include <string>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& vertSrc, const std::string& fragSrc);
	Shader(const std::string& filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetFloat(const std::string& name, float value);
	void SetFloat3(const std::string& name, const glm::vec3& value);
	void SetMat4(const std::string& name, const glm::mat4& value);

private:
	ShaderProgramSource ParseShaderFile(const std::string& filename);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShaderProgram(const std::string& vertSrc, const std::string& fragSrc);

private:
	unsigned int m_RendererID;
};
