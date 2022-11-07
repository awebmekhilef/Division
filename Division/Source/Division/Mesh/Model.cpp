#include "Model.h"

#include "../Rendering/Texture.h"
#include "../Rendering/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Model::Model(const std::string& filepath)
{
	Assimp::Importer imp;
	const aiScene* aiScene = imp.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	m_FileDirectory = filepath.substr(0, filepath.find_last_of('/'));

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

void Model::SetPosition(const glm::vec3& position)
{
	m_Position = position;
	m_Dirty = true;
}

void Model::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
	m_Dirty = true;
}

void Model::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
	m_Dirty = true;
}

glm::vec3 Model::GetPosition() const
{
	return m_Position;
}

glm::vec3 Model::GetRotation() const
{
	return m_Rotation;
}

glm::vec3 Model::GetScale() const
{
	return m_Scale;
}

glm::vec3 Model::GetWorldPosition()
{
	return glm::vec3(GetTransform() * glm::vec4(m_Position, 1.0f));
}

glm::vec3 Model::GetWorldScale()
{
	glm::mat4 transform = GetTransform();
	glm::vec3 scale = glm::vec3(transform[0][0], transform[2][1], transform[2][2]);

	return scale;
}

glm::mat4 Model::GetTransform()
{
	if (m_Dirty)
		UpdateTransform();

	return m_Transform;
}

void Model::UpdateTransform()
{
	std::cout << "Here";

	if (m_Dirty) 
	{
		m_Transform = glm::translate(m_Transform, m_Position);
		m_Transform = glm::rotate(m_Transform, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_Transform = glm::rotate(m_Transform, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_Transform = glm::rotate(m_Transform, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		m_Transform = glm::scale(m_Transform, m_Scale);

		if (m_Parent)
			m_Transform = m_Parent->m_Transform * m_Transform;

		for (size_t i = 0; i < m_Children.size(); i++)
		{
			m_Children[i]->m_Dirty = true;
			m_Children[i]->UpdateTransform();
		}
	}

	m_Dirty = false;
}

void Model::AddChild(Model* model)
{
	// If to be child already has parent then remove from current parent
	if (model->m_Parent)
		model->m_Parent->RemoveChild(model);

	model->m_Parent = this;
	m_Children.push_back(model);
}

void Model::RemoveChild(Model* model)
{
	auto it = std::find(m_Children.begin(), m_Children.end(), model);
	if (it != m_Children.end()) 
	{
		m_Children.erase(it);
		model->m_Parent = nullptr;
	}
}

unsigned int Model::GetChildCount()
{
	return m_Children.size();
}

std::vector<Model*> Model::GetChildren()
{
	return m_Children;
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

	std::string file = m_FileDirectory + "/" + path.C_Str();

	if (m_LoadedTextures.find(file) == m_LoadedTextures.end())
	{
		Texture* texture = new Texture(file);
		m_LoadedTextures[file] = texture;

		return texture;
	}
	else
		return m_LoadedTextures.at(file);
}
