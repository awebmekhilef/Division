#pragma once

#include <glm/glm.hpp>

#include <vector>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV;
};

class Mesh
{
public:
	// Could've had a draw method here in Mesh however it would be doing too many things
	// and it's better to have all render state in a single place
	friend class Renderer;

	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	void Finalize();

protected:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

private:
	unsigned int m_VAO;
};
