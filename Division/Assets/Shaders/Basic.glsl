// SHADER VERTEX
#version 430 core

layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aUV;

out vec2 vUV;
out vec3 vNormal;
out vec3 vFragPos;

uniform mat4 uViewProj;
uniform mat4 uModel;

void main()
{
	gl_Position = uViewProj * uModel * vec4(aPosition, 1.0);

	vUV = aUV;
	vNormal = aNormal; // Assumes we wont be scaling the model
	vFragPos = vec3(uModel * vec4(aPosition, 1.0));
}

// SHADER FRAGMENT
#version 430 core

in vec2 vUV;
in vec3 vNormal;
in vec3 vFragPos;

out vec4 FragColor;

uniform vec3 uCameraPos;

// Light attributes (only one for now)
uniform vec3 uLightPosition;
uniform vec3 uLightAmbient;
uniform vec3 uLightDiffuse;
uniform vec3 uLightSpecular;

// Material attributes
uniform sampler2D uDiffuse;
uniform sampler2D uSpecular;
uniform float uShininess;

void main() 
{
	// Ambient
    vec3 ambient = uLightAmbient * texture(uDiffuse, vUV).rgb;
  	
    // Diffuse 
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLightPosition - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uLightDiffuse * diff * texture(uDiffuse, vUV).rgb;  
    
    // Specular
    vec3 viewDir = normalize(uCameraPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
    vec3 specular = uLightSpecular * spec * texture(uSpecular, vUV).rgb;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
