#include "TextureCube.h"

#include <glad/glad.h>
#include <stb_image/stb_image.h>

TextureCube::TextureCube(const std::string& folder, const std::string& ext)
	: TextureCube(
		folder + "right" + ext,
		folder + "left" + ext,
		folder + "top" + ext,
		folder + "bottom" + ext,
		folder + "front" + ext,
		folder + "back" + ext
	)
{
}

TextureCube::TextureCube(
	const std::string& right, 
	const std::string& left, 
	const std::string& top, 
	const std::string& bottom, 
	const std::string& front, 
	const std::string& back)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	stbi_set_flip_vertically_on_load(0);

	std::string faces[] = { right, left, top, bottom, front, back };

	for (int i = 0; i < 6; i++)
	{
		int w, h;
		unsigned char* data = stbi_load(faces[i].c_str(), &w, &h, NULL, 4);

		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
		);

		stbi_image_free(data);
	}
}

void TextureCube::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
}
