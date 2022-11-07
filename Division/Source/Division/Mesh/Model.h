#pragma once

#include "Mesh.h"
#include "../Rendering/Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <unordered_map>

class Model
{
public:
	Model(const std::string& filepath);

	unsigned int GetMeshCount() const;
	const std::pair<Mesh*, Material*>& GetMeshPair(unsigned int index) const;

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	glm::vec3 GetWorldPosition();

	glm::mat4 GetTransform();
	void UpdateTransform();

	void AddChild(Model* model);
	void RemoveChild(Model* model);
	unsigned int GetChildCount();
	std::vector<Model*> GetChildren();

private:
	void ProcessNode(aiNode* aiNode, const aiScene* aiScene);
	std::pair<Mesh*, Material*> ProcessMesh(aiMesh* aiMesh, const aiScene* aiScene);
	Material* ProcessMaterial(aiMaterial* aiMaterial, const aiScene* aiScene);
	Texture* LoadTexture(aiMaterial* aiMaterial, aiTextureType type);

private:
	std::vector<std::pair<Mesh*, Material*>> m_Meshes;

	std::string m_FileDirectory; // Assumes textures are stored relative to model
	std::unordered_map<std::string, Texture*> m_LoadedTextures; // Better handled by a resource manager

	std::vector<Model*> m_Children;
	Model* m_Parent;

	glm::mat4 m_Transform = glm::mat4(1.0f);
	glm::vec3 m_Position = glm::vec3(0.0f);
	glm::vec3 m_Rotation = glm::vec3(0.0f);
	glm::vec3 m_Scale = glm::vec3(1.0f);

	bool m_Dirty = true;
};
