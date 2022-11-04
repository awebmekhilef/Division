#pragma once

class Mesh;
class Material;
class Camera;

class Renderer
{
public:
	static void Render(Mesh* mesh, Material* material, Camera* camera);
};
