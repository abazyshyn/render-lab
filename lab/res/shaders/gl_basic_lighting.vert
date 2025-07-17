#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCoordinate;

layout(std140, binding = 0) uniform ub_Matrices
{
    mat4 u_ProjectionMatrix;
    mat4 u_ViewMatrix;
};

uniform mat3 u_NormalMatrix;
uniform mat4 u_ModelMatrix;

out VSOut
{
	vec3 vs_Normal;
	vec3 vs_FragmentPosition;
    vec2 vs_TextureCoordinate;
} vsOut;

void main()
{
    mat4 PVM = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix;
    gl_Position = PVM * vec4(a_Position, 1.0); 

    vsOut.vs_Normal = a_Normal * u_NormalMatrix;
    vsOut.vs_FragmentPosition = vec3(u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0));
    vsOut.vs_TextureCoordinate = a_TextureCoordinate;
}