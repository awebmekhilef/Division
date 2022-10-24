// SHADER VERTEX
#version 430 core

layout(location=0) in vec2 aPosition;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoords;

out vec3 vColor;
out vec2 vTexCoords;

uniform mat4 uMVP;

void main()
{
	gl_Position = uMVP * vec4(aPosition, 0.0, 1.0);

	vColor = aColor;
	vTexCoords = aTexCoords;
}

// SHADER FRAGMENT
#version 430 core

in vec3 vColor;
in vec2 vTexCoords;

out vec4 Color;

uniform sampler2D uTexture;

void main() 
{
	Color = texture(uTexture, vTexCoords) * vec4(vColor, 1.0);
}
