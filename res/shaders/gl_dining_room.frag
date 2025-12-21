#version 460 core

in VSOut
{
    vec2 vs_UV;
    // vec3 vs_Normal;
    // vec3 vs_FragmentPos;
} fsIn;

struct Material_s
{
    sampler2D m_DiffuseTexture1;
};

uniform Material_s u_Material;

out vec4 color;

void main ()
{
    color = texture(u_Material.m_DiffuseTexture1, fsIn.vs_UV);
}