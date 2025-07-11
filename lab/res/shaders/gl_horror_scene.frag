#version 460 core

uniform sampler2D u_DiffuseTexture1;

in VSOut
{
    vec2 vs_textureCoordinate;
} fsIn;

out vec4 resultedColor;

void main()
{
    resultedColor = texture(u_DiffuseTexture1, fsIn.vs_textureCoordinate);
}