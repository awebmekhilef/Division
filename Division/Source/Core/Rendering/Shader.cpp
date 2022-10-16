#include "Shader.h"

#include <glad/glad.h>
#include <iostream>

Shader::Shader(const std::string& vertSrc, const std::string& fragSrc)
{
	m_RendererID = glCreateProgram();

	unsigned int vShader = CompileShader(GL_VERTEX_SHADER, vertSrc);
	unsigned int fShader = CompileShader(GL_FRAGMENT_SHADER, fragSrc);

	glAttachShader(m_RendererID, vShader);
	glAttachShader(m_RendererID, fShader);
	glLinkProgram(m_RendererID);
	glUseProgram(m_RendererID);

	// Delete flags it for deletion but only once it has been detached
	// sometimes you want to leave it in memory to debug it
	glDetachShader(m_RendererID, vShader);
	glDetachShader(m_RendererID, fShader);
	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetFloat(const std::string& name, float value)
{
	unsigned int loc = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1f(loc, value);
}

void Shader::SetFloat3(const std::string& name, float v0, float v1, float v2)
{
	unsigned int loc = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform3f(loc, v0, v1, v2);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);

	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		// Can just use a vector of chars or heap allocate array
		// but I want to keep it old school (and flex a little)
		char* log = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, log);

		std::cout << log << std::endl;
	}

	return id;
}
