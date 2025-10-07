#version 460 core

uniform mat4   u_ViewMatrix;
uniform mat4   u_ProjectionMatrix;
uniform vec3   u_CameraWorldPos;
uniform float  u_GridSize = 100.0;

const vec3 gridPos[4] = vec3[4](
    vec3(-1.0, 0.0, -1.0),
    vec3( 1.0, 0.0, -1.0),
    vec3( 1.0, 0.0,  1.0),
    vec3(-1.0, 0.0,  1.0)
);

const int gridIndices[6] = int[6](0, 2, 1, 2, 0, 3);

out vec3 curGridVertexWorldPos;

void main()
{
    int curGridVertexIndex = gridIndices[gl_VertexID];
    vec3 curGridVertexPos3 = gridPos[curGridVertexIndex] * u_GridSize;

    curGridVertexPos3.x += u_CameraWorldPos.x;
    curGridVertexPos3.z += u_CameraWorldPos.z;

    vec4 curGridVertexPos4 = vec4(curGridVertexPos3, 1.0);

    gl_Position = u_ProjectionMatrix * u_ViewMatrix * curGridVertexPos4;

    curGridVertexWorldPos = vec3(curGridVertexPos3);
}
