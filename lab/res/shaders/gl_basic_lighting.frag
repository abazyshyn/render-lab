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
	// vec3 m_AmbientColor;
	vec3 m_DiffuseColor;
	// vec3 m_SpecularColor;
};

uniform Material_s u_Material;
uniform DirectionalLight_s u_DirectionalLight;

in VSOut
{
	vec3 vs_Normal;
	vec3 vs_FragmentPosition;
    vec2 vs_TextureCoordinate;
} fsIn;

out vec4 resultedColor;

// Returns color that is the result of the directional light
vec3 CalculateDirectionalLight(vec3 t_Normal);

void main()
{
    vec3 color = vec3(0.0);
	vec3 normal = normalize(fsIn.vs_Normal);

	color += CalculateDirectionalLight(normal);
    
	resultedColor = vec4(color, 1.0);
}

vec3 CalculateDirectionalLight(vec3 t_Normal)
{
	vec3 lightDirection = normalize(u_DirectionalLight.m_Position - fsIn.vs_FragmentPosition);

	float diffuseImpact = max(dot(lightDirection, t_Normal), 0.0);
	vec3 diffuseColor = diffuseImpact * u_DirectionalLight.m_DiffuseColor * texture(u_Material.m_DiffuseTexture1, fsIn.vs_TextureCoordinate).rgb;

	// TODO: specular color
    return diffuseColor;
}