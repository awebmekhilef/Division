#pragma once

#include "glm/glm.hpp"

#include <vector>

class Mesh;
class Cube;
class Model;
class Material;
class Camera;
class Shader;
struct Light;

class Renderer
{
public:
	static void Init();

	static void Render(Mesh* mesh, Material* material, Camera* camera, const glm::mat4& transform);
	static void Render(Model* model, Camera* camera);
	static void RenderLight(Light* light, Camera* camera);

	static void AddLight(Light* light);

	static Shader* GetDefaultShader();

private:
	static std::vector<Light*> m_Lights;

	// Not the best place (move to resource manager)
	static Shader* m_DefaultShader;
	static Material* m_DebugLightMaterial;
	static Cube* m_DebugLightMesh;
};
