#pragma once

class Texture;
class TextureCube;

enum class ShaderDataType
{
	Int,
	Float,
	Vec3,
	Mat4,
	Texture2D,
	TextureCube
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

	union
	{
		Texture* Texture;
		TextureCube* TextureCube;
	};
};
