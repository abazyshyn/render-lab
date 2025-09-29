#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

out VSOut
{
    vec3 vs_Normal;
} vsOut;

void main()
{
    gl_Position = u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
    
    mat3 normalMatrix = mat3(transpose(inverse(u_ViewMatrix * u_ModelMatrix)));
    vsOut.vs_Normal = normalize(vec3(vec4(normalMatrix * a_Normal, 0.0)));
}