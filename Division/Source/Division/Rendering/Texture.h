#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(unsigned int slot = 0) const;

private:
	unsigned int m_RendererID;

	// Can be used to hot releod in future using glTexSubImage2D 
	// https://github.com/ThomasMonkman/filewatch
	std::string m_Filepath;
};
