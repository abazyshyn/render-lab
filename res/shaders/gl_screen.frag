#version 460 core

uniform sampler2D screenTexture;

in vec2 textureCoordinate;
out vec4 resultedColor;

void main()
{
	resultedColor = texture(screenTexture, textureCoordinate);
}