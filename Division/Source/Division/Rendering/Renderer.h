#pragma once

#include "glm/glm.hpp"

#include <vector>

class Mesh;
class Model;
class Material;
class Camera;
class Shader;
struct Light;

class Renderer
{
public:
	static void Render(Mesh* mesh, Material* material, Camera* camera, const glm::mat4& transform);
	static void Render(Model* model, Camera* camera);

	static void AddLight(Light* light);

	static Shader* GetDefaultShader();

private:
	static std::vector<Light*> m_Lights;
	static Shader* m_DefaultShader;
};
