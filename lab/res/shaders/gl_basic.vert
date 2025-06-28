#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCoordinate;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec2 textureCoordinate;

void main()
{
    mat4 PVM = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix;

    gl_Position = PVM * vec4(a_Position, 1.0);

    textureCoordinate = a_TextureCoordinate;
}