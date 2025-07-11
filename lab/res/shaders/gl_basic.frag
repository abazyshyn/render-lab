#version 460 core

in VSOut
{
    vec2 vs_textureCoordinate;
} fsIn;

out vec4 resultedColor;

void main()
{
    resultedColor = vec4(0.122, 0.122, 0.122, 1.0);
}