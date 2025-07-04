#version 460 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec3 textureCoordinate;

void main()
{
    vec4 pos = u_ProjectionMatrix * u_ViewMatrix * vec4(a_Position, 1.0);
    
    gl_Position = pos.xyww;

    textureCoordinate = a_Position;
}