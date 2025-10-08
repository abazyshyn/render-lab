#version 460 core

in VSOut
{
    vec3 vs_Normal;
	vec3 vs_FragmentPosition;
} fsIn;

struct Material_s
{
	vec3  m_AmbientColor;
	vec3  m_DiffuseColor;
	vec3  m_SpecularColor;
	float m_Shininess;
};

struct DirectionalLight_s
{
    vec3 m_AmbientColor;
	vec3 m_DiffuseColor;
	vec3 m_SpecularColor;
};

uniform Material_s waterMaterial = Material_s(
	vec3(     0.1, 0.18725,   0.1745),
	vec3(   0.396, 0.74151,  0.69102),
	vec3(0.297254, 0.30829, 0.306678),
	0.1
);

uniform DirectionalLight_s dirLight = DirectionalLight_s(
	vec3(0.4, 0.4, 0.4),
	vec3(0.4, 0.4, 0.4),
	vec3(0.5, 0.5, 0.5)
);

uniform vec3 u_DirLightPosition;

out vec4 resultColor;

void main()
{
	vec3 normal = normalize(fsIn.vs_Normal);

	vec3 ambientColor = dirLight.m_AmbientColor * waterMaterial.m_AmbientColor;

	vec3 lightDirection = normalize(u_DirLightPosition - fsIn.vs_FragmentPosition);
	float diffuseImpact = max(dot(lightDirection, normal), 0.0);
	vec3 diffuseColor = dirLight.m_DiffuseColor * waterMaterial.m_DiffuseColor * diffuseImpact;

	vec3 viewDirection = normalize(-fsIn.vs_FragmentPosition);
	vec3 reflectLightDirection = reflect(-lightDirection, viewDirection);
	float specularImpact = pow(max(dot(viewDirection, reflectLightDirection), 0.0), waterMaterial.m_Shininess);
	vec3 specularColor = dirLight.m_SpecularColor * waterMaterial.m_SpecularColor * specularImpact;

	resultColor = vec4(ambientColor + diffuseColor + specularColor, 1.0);
}