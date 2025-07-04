#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TextureCoordinate;

out vec2 textureCoordinate;

void main()
{
	gl_Position = vec4(a_Position.x, a_Position.y, 0.0, 1.0);

	textureCoordinate = a_TextureCoordinate;
}