// SHADER VERTEX
#version 430 core
layout (location = 0) in vec3 aPosition;

out vec3 vUV;

// This is technically the view matrix,
// however due to the current design the user can only pass in model matrices
// as the view matrix is passed in automatically.
uniform mat4 uModel;
uniform mat4 uProj;

void main()
{
    vUV = aPosition;
    gl_Position = uProj * uModel * vec4(aPosition, 1.0);
}

// SHADER FRAGMENT
#version 430 core

out vec4 FragColor;

in vec3 vUV;

uniform samplerCube uSkybox;

void main()
{    
    FragColor = texture(uSkybox, vUV);
}
