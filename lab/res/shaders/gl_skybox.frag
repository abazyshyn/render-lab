#version 460 core

in vec3 textureCoordinate;
out vec4 resultedColor;

uniform samplerCube skybox;

void main()
{
	resultedColor = texture(skybox, textureCoordinate);
}