#version 460 core

layout(location = 0) in vec3 a_Position;

layout(std140, binding = 0) uniform ub_Matrices
{
    mat4 u_ProjectionMatrix;
    mat4 u_ViewMatrix;
};

out vec3 textureCoordinate;

void main()
{
    mat4 view = mat4(mat3(u_ViewMatrix));

    vec4 pos = u_ProjectionMatrix * view * vec4(a_Position, 1.0);
    
    gl_Position = pos.xyww;

    textureCoordinate = a_Position;
}