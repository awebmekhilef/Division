#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Shader::Shader(const std::string& vertSrc, const std::string& fragSrc)
{
	m_RendererID = CreateShaderProgram(vertSrc, fragSrc);
}

Shader::Shader(const std::string& filename)
{
	ShaderProgramSource src = ParseShaderFile(filename);
	m_RendererID = CreateShaderProgram(src.VertexSource, src.FragmentSource);
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

void Shader::UploadInt(const std::string& name, int value)
{
	unsigned int loc = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1i(loc, value);
}

void Shader::UploadFloat(const std::string& name, float value)
{
	unsigned int loc = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1f(loc, value);
}

void Shader::UploadVec3(const std::string& name, const glm::vec3& value)
{
	unsigned int loc = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform3fv(loc, 1, glm::value_ptr(value));
}

void Shader::UploadMat4(const std::string& name, const glm::mat4& value)
{
	unsigned int loc = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

ShaderProgramSource Shader::ParseShaderFile(const std::string& filename)
{
	// Since shaders are stored in the same file
	// we need to know which one we're parsing
	enum ShaderType { None = -1, Vertex, Fragment };

	std::stringstream ss[2];
	ShaderType currentShader = ShaderType::None;

	std::ifstream file(filename);

	std::string line;
	while (std::getline(file, line))
	{
		if (line.find("// SHADER") != std::string::npos)
		{
			if (line.find("VERTEX") != std::string::npos)
				currentShader = ShaderType::Vertex;
			else if (line.find("FRAGMENT") != std::string::npos)
				currentShader = ShaderType::Fragment;
		}
		else
		{
			if (currentShader != ShaderType::None)
				ss[(int)currentShader] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
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

unsigned int Shader::CreateShaderProgram(const std::string& vertSrc, const std::string& fragSrc)
{
	m_RendererID = glCreateProgram();

	unsigned int vShader = CompileShader(GL_VERTEX_SHADER, vertSrc);
	unsigned int fShader = CompileShader(GL_FRAGMENT_SHADER, fragSrc);

	glAttachShader(m_RendererID, vShader);
	glAttachShader(m_RendererID, fShader);
	glLinkProgram(m_RendererID);
	glUseProgram(m_RendererID);

	// Delete flags it for deletion but only once it has been detached
	// sometimes you want to leave it in memory to debug
	glDetachShader(m_RendererID, vShader);
	glDetachShader(m_RendererID, fShader);
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return m_RendererID;
}