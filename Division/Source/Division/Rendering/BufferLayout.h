#pragma once

#include <vector>
#include <glad/glad.h>

// This should be encapsulated in an enum shader data type
// so we can easily use other APIs
static unsigned int OpenGLShaderDataTypeSize(unsigned int type)
{
	switch (type)
	{
		case GL_FLOAT: return sizeof(float);
	}

	return 0;
}

struct BufferLayoutElement
{
	unsigned int Dimensions;
	unsigned int Type;
	bool Normalize;
};

class BufferLayout
{
public:
	void Push(unsigned int dimensions, unsigned int type, bool normalize);

	inline int GetStride() const { return m_Stride; }
	inline const std::vector<BufferLayoutElement>& GetElements() const { return m_Elements; }

private:
	std::vector<BufferLayoutElement> m_Elements;
	int m_Stride;
};
