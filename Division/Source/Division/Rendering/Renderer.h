#pragma once

class Mesh;
class Material;

class Renderer
{
public:
	static void Render(Mesh* mesh, Material* material);
};
