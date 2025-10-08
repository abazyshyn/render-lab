#version 460 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Norm;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Pos, 1.0);
}