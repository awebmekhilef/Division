#include "Model.h"

#include "../Rendering/Texture.h"
#include "../Rendering/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Model::Model(const std::string& filepath)
{
	Assimp::Importer imp;
	const aiScene* aiScene = imp.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	m_Directory = filepath.substr(0, filepath.find_last_of('/'));

	ProcessNode(aiScene->mRootNode, aiScene);
}

unsigned int Model::GetMeshCount() const
{
	return m_Meshes.size();
}

const std::pair<Mesh*, Material*>& Model::GetMeshPair(unsigned int index) const
{
	return m_Meshes[index];
}

void Model::ProcessNode(aiNode* aiNode, const aiScene* aiScene)
{
	for (size_t i = 0; i < aiNode->mNumMeshes; i++)
	{
		aiMesh* aiMesh = aiScene->mMeshes[aiNode->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(aiMesh, aiScene));
	}

	for (size_t i = 0; i < aiNode->mNumChildren; i++)
	{
		ProcessNode(aiNode->mChildren[i], aiScene);
	}
}

std::pair<Mesh*, Material*> Model::ProcessMesh(aiMesh* aiMesh, const aiScene* aiScene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < aiMesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.Position.x = aiMesh->mVertices[i].x;
		vertex.Position.y = aiMesh->mVertices[i].y;
		vertex.Position.z = aiMesh->mVertices[i].z;

		vertex.Normal.x = aiMesh->mNormals[i].x;
		vertex.Normal.y = aiMesh->mNormals[i].y;
		vertex.Normal.z = aiMesh->mNormals[i].z;

		// Not all meshes have texture coordinates
		if (aiMesh->mTextureCoords[0])
		{
			vertex.UV.x = aiMesh->mTextureCoords[0][i].x;
			vertex.UV.y = aiMesh->mTextureCoords[0][i].y;
		}
		else
			vertex.UV = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (size_t i = 0; i < aiMesh->mNumFaces; i++)
	{
		aiFace face = aiMesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	Mesh* mesh = new Mesh(vertices, indices);
	mesh->Finalize();
	
	// Create a material for each mesh
	Material* mat = ProcessMaterial(aiScene->mMaterials[aiMesh->mMaterialIndex], aiScene);

	return std::make_pair(mesh, mat);
}

Material* Model::ProcessMaterial(aiMaterial* aiMaterial, const aiScene* scene)
{
	Material* mat = new Material(Renderer::GetDefaultShader());

	if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		mat->SetTexture("uDiffuse", LoadTexture(aiMaterial, aiTextureType_DIFFUSE), 0);

	if (aiMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
		mat->SetTexture("uSpecular", LoadTexture(aiMaterial, aiTextureType_SPECULAR), 1);

	mat->SetFloat("uShininess", 64.0f);

	return mat;
}

Texture* Model::LoadTexture(aiMaterial* aiMaterial, aiTextureType type)
{
	aiString path;
	aiMaterial->GetTexture(type, 0, &path);

	std::string file = m_Directory + "/" + path.C_Str();

	if (m_LoadedTextures.find(file) == m_LoadedTextures.end())
	{
		Texture* texture = new Texture(file);
		m_LoadedTextures[file] = texture;

		return texture;
	}
	else
		return m_LoadedTextures.at(file);
}