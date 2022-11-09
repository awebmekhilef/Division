#pragma once

#include <string>

class TextureCube
{
public:
	TextureCube(const std::string& folder, const std::string& ext = ".jpg");
	TextureCube(const std::string& right, 
				const std::string& left, 
				const std::string& top, 
				const std::string& bottom,
				const std::string& front,
				const std::string& back);

	void Bind(unsigned int slot = 0) const;

private:
	unsigned int m_RendererID;
};

