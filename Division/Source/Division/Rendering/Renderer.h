#pragma once

class Mesh;
class Shader;

class Renderer
{
public:
	static void Render(Mesh* mesh, Shader* shader);
};
