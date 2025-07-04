#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec3 position;
out vec3 normal;

void main()
{
    position = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
    normal = mat3(transpose(inverse(u_ModelMatrix))) * a_Normal;

    mat4 PV = u_ProjectionMatrix * u_ViewMatrix;

    gl_Position = PV * vec4(position, 1.0);
}