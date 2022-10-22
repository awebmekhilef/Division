#include "BufferLayout.h"

#include <glad/glad.h>

void BufferLayout::Push(unsigned int dimensions, unsigned int type, bool normalize)
{
	m_Elements.push_back({ dimensions, type, normalize });
	m_Stride += dimensions * OpenGLShaderDataTypeSize(type);
}
