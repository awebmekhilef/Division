#pragma once

#include <vector>

class Mesh;
class Material;
class Camera;
class Light;

class Renderer
{
public:
	static void Render(Mesh* mesh, Material* material, Camera* camera);

	static void AddLight(Light* light);

private:
	static std::vector<Light*> m_Lights;
};
