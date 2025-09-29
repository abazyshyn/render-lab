#version 460 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

uniform mat4 u_ProjectionMatrix;

in VSOut
{
    vec3 vs_Normal;
} gsIn[];

void GenerateLine(const unsigned int ct_Index);

void main()
{
    for (unsigned int i = 0; i < 3; ++i)
    {
        GenerateLine(i);
    }
}

void GenerateLine(const unsigned int ct_Index)
{
    const float magnitude = 0.02;

    gl_Position = u_ProjectionMatrix * gl_in[ct_Index].gl_Position;
    EmitVertex();

    gl_Position = u_ProjectionMatrix * (gl_in[ct_Index].gl_Position + vec4(gsIn[ct_Index].vs_Normal, 0.0) * magnitude);
    EmitVertex();
    EndPrimitive();
}