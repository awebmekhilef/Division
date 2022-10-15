#pragma once

class VertexBuffer
{
public:
	VertexBuffer(float* vertices, int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID;
};

class IndexBuffer
{
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }

private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};
