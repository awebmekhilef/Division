#pragma once

#include "VertexArray.h"
#include "Shader.h"

#include <glad/glad.h>

class Renderer
{
public:
	static void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader);
};
