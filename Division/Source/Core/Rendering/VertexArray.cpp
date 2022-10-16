#include "VertexArray.h"

#include <glad/glad.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(VertexBuffer& buffer, BufferLayout& layout)
{
	auto elements = layout.GetElements();
	unsigned char offset = 0;

	for (int i = 0; i < elements.size(); i++)
	{
		auto element = elements[i];

		// FIXME: Adding multiple buffers overwrites layout (keep track of count?)
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.Dimensions, element.Type,
			element.Normalize ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)offset);

		offset += element.Dimensions;
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
