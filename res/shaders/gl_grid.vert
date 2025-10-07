#version 460 core

uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

const vec3 gridPos[4] = vec3[4](
    vec3(-1.0, 0.0, -1.0),
    vec3(1.0, 0.0, -1.0),
    vec3(1.0, 0.0, 1.0),
    vec3(-1.0, 0.0, 1.0));

const int gridIndices[6] = int[6](0, 2, 1, 2, 0, 3);

void main()
{
    int idx = gridIndices[gl_VertexID];
    vec4 pos = vec4(gridPos[idx], 1.0);
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * pos;
}
