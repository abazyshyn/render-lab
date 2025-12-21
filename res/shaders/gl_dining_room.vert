#version 460 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_UV;

uniform mat4  u_ModelMatrix;
uniform mat4  u_ViewMatrix;
uniform mat4  u_ProjectionMatrix;

out VSOut
{
    vec2 vs_UV;
    // vec3 vs_Normal;
    // vec3 vs_FragmentPos;
} vsOut;

void main ()
{
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Pos, 1.0);
    
    vsOut.vs_UV = a_UV;
    // vsOut.vs_Normal = a_Normal;
    // vsOut.vs_FragmentPos = vec3(u_ModelMatrix * a_Pos);
}