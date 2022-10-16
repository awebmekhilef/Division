#pragma once

#include <string>

class Shader
{
public:
	Shader(const std::string& vertSrc, const std::string& fragSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);

private:
	unsigned int m_RendererID;
};
