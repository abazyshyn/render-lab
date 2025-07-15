#version 460 core

struct Material_s
{	
	sampler2D m_DiffuseTexture1;
	sampler2D m_DiffuseTexture2;
	sampler2D m_DiffuseTexture3;
	sampler2D m_DiffuseTexture4;
	sampler2D m_DiffuseTexture5;
	sampler2D m_DiffuseTexture6;
	sampler2D m_DiffuseTexture7;
			  
	sampler2D m_SpecularTexture1;
	sampler2D m_SpecularTexture2;
	sampler2D m_SpecularTexture3;
	sampler2D m_SpecularTexture4;
	sampler2D m_SpecularTexture5;
	sampler2D m_SpecularTexture6;
	sampler2D m_SpecularTexture7;
};

struct DirectionalLight_s
{
	vec3 m_Position;
	vec3 m_AmbientColor;
	vec3 m_DiffuseColor;
	vec3 m_SpecularColor;
};

uniform Material_s u_Material;
uniform DirectionalLight_s u_DirectionalLight;

in VSOut
{
    vec2 vs_TextureCoordinate;
	vec3 vs_Normal;
	vec3 vs_FragmentPosition;
} fsIn;

out vec4 resultedColor;

vec3 CalculateDirectionalLight();

void main()
{
    
}

vec3 CalculateDirectionalLight()
{
    vec3 lightDirection = normalize(u_DirectionalLight.m_Position - fsIn.vs_FragmentPosition);

	float diffuseImpact = max(dot(lightDirection, fsIn.vs_Normal), 0.0);

    return vec3(0);
}