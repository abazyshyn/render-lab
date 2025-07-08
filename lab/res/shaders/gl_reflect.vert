#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

layout(std140, binding = 0) uniform ub_Matrices
{
    mat4 u_ProjectionMatrix;
    mat4 u_ViewMatrix;
};

uniform mat4 u_ModelMatrix;

out VSOut
{
    vec3 position;
    vec3 normal;
} vsOut;

void main()
{
    vsOut.position = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
    vsOut.normal = mat3(transpose(inverse(u_ModelMatrix))) * a_Normal;

    mat4 PV = u_ProjectionMatrix * u_ViewMatrix;

    gl_Position = PV * vec4(vsOut.position, 1.0);
}