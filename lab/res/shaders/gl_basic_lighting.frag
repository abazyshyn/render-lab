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

	float m_Shininess;
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
	vec3 vs_NormalVector;
	vec3 vs_FragmentPosition;
    vec2 vs_TextureCoordinate;
} fsIn;

out vec4 resultedColor;

// Checks texture's alpha value, fragment will be discarded if alpha is less then 0.1
void DiscardFragment();

// Returns color that is the result of the directional light
vec3 CalculateDirectionalLight(vec3 t_NormalVector, vec3 t_ViewDirectionVector);

void main()
{
    DiscardFragment();

    vec3 color = vec3(0.0);
	vec3 normalVector = normalize(fsIn.vs_NormalVector);
	vec3 viewDirectionVector = normalize(-fsIn.vs_FragmentPosition);

	color += CalculateDirectionalLight(normalVector, viewDirectionVector);
    
	resultedColor = vec4(color, 1.0);
}

void DiscardFragment()
{
	if (texture(u_Material.m_DiffuseTexture1, fsIn.vs_TextureCoordinate).a < 0.1 ||
	    texture(u_Material.m_SpecularTexture1, fsIn.vs_TextureCoordinate).a < 0.1)
	{
	    discard;
	}
}

vec3 CalculateDirectionalLight(vec3 t_NormalVector, vec3 t_ViewDirectionVector)
{
	vec3 ambientColor = u_DirectionalLight.m_AmbientColor * texture(u_Material.m_DiffuseTexture1, fsIn.vs_TextureCoordinate).rgb;
	
	vec3 lightDirectionVector = normalize(u_DirectionalLight.m_Position - fsIn.vs_FragmentPosition);

	float diffuseImpact = max(dot(lightDirectionVector, t_NormalVector), 0.0);
	vec3 diffuseColor = diffuseImpact * u_DirectionalLight.m_DiffuseColor * texture(u_Material.m_DiffuseTexture1, fsIn.vs_TextureCoordinate).rgb;

	vec3 reflectedLightDirectionVector = reflect(-lightDirectionVector, t_NormalVector);
	float specularImpact = pow(max(dot(t_ViewDirectionVector, reflectedLightDirectionVector), 0.0), u_Material.m_Shininess);
	
	if (specularImpact > 0.0 && u_Material.m_Shininess > 0.0)
	{
	    vec3 specularColor = specularImpact * u_DirectionalLight.m_SpecularColor * texture(u_Material.m_SpecularTexture1, fsIn.vs_TextureCoordinate).rgb;

		return (ambientColor + diffuseColor + specularColor);
	}


    return (ambientColor + diffuseColor);
}