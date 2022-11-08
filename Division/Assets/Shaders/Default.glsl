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
	vNormal = mat3(transpose(inverse(uModel))) * aNormal;
	vFragPos = vec3(uModel * vec4(aPosition, 1.0));
}

// SHADER FRAGMENT
#version 430 core

in vec2 vUV;
in vec3 vNormal;
in vec3 vFragPos;

out vec4 FragColor;

uniform vec3 uCameraPos;

struct Light 
{
    vec3 Position;
    vec3 Diffuse;
    vec3 Specular;
};

#define MAX_LIGHTS 128
uniform Light uLights[MAX_LIGHTS];
uniform int uLightCount;


// Material attributes
uniform sampler2D uDiffuse;
uniform sampler2D uSpecular;
uniform float uShininess;

// Should be stored in scene data
vec3 uAmbient = vec3(0.3f, 0.3f, 0.3f);

void main() 
{
    vec3 result;

    for (int i = 0; i < uLightCount; i++)
    {
        Light light = uLights[i];

	    // Ambient
        vec3 ambient = uAmbient * texture(uDiffuse, vUV).rgb;
  	    
        // Diffuse 
        vec3 norm = normalize(vNormal);
        vec3 lightDir = normalize(light.Position - vFragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.Diffuse * diff * texture(uDiffuse, vUV).rgb;  
        
        // Specular
        vec3 viewDir = normalize(uCameraPos - vFragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
        vec3 specular = light.Specular * spec * texture(uSpecular, vUV).rgb;  
            
        result += ambient + diffuse + specular;
    }

    FragColor = vec4(result, 1.0);
}
