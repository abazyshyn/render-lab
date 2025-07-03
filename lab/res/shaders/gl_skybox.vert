#version 460 core

layout(location = 0) in vec3 a_Pos;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec3 textureCoordinate;

void main()
{
   gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(a_Pos, 1.0);

   textureCoordinate = a_Pos;
}