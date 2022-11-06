#pragma once

class Texture;

enum class ShaderDataType
{
	Int,
	Float,
	Vec3,
	Mat4,
	Texture2D
};

struct UniformValue
{
	ShaderDataType Type;

	// Not the biggest fan of this 
	// since it takes up the size of the max (64 bytes)
	union
	{
		int Int;
		float Float;
		glm::vec3 Vec3;
		glm::mat4 Mat4;
	};
};

struct UniformSamplerValue
{
	ShaderDataType Type;
	unsigned int Unit;
	Texture* Texture;
};
