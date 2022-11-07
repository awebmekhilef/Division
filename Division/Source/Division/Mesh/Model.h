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

private:
	void ProcessNode(aiNode* aiNode, const aiScene* aiScene);
	std::pair<Mesh*, Material*> ProcessMesh(aiMesh* aiMesh, const aiScene* aiScene);
	Material* ProcessMaterial(aiMaterial* aiMaterial, const aiScene* aiScene);
	Texture* LoadTexture(aiMaterial* aiMaterial, aiTextureType type);


private:
	std::vector<std::pair<Mesh*, Material*>> m_Meshes;

	std::string m_Directory; // Assumes textures are stored relative to model
	std::unordered_map<std::string, Texture*> m_LoadedTextures; // Better handled by a resource manager
};
