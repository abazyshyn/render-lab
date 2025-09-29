#version 460 core

uniform samplerCube skybox;

in vec3 textureCoordinate;
out vec4 resultedColor;

void main()
{
	resultedColor = texture(skybox, textureCoordinate);
}