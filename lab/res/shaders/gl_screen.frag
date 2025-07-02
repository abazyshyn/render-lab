#version 460 core

in vec2 textureCoordinate;
out vec4 resultedColor;

uniform sampler2D screenTexture;

void main()
{
	resultedColor = texture(screenTexture,textureCoordinate);
}