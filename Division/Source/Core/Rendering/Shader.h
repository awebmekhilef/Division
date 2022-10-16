#pragma once

#include <string>

class Shader
{
public:
	Shader(const std::string& vertSrc, const std::string& fragSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetFloat(const std::string& name, float value);
	void SetFloat3(const std::string& name, float v0, float v1, float v2);

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);

private:
	unsigned int m_RendererID;
};
