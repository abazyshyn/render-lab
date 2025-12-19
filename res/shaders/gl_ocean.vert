#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

// uniform mat3  u_NormalMatrix;
uniform mat4  u_ModelMatrix;
uniform mat4  u_ViewMatrix;
uniform mat4  u_ProjectionMatrix;
uniform float u_Time;

out VSOut
{
    vec3 vs_Normal;
	vec3 vs_FragmentPosition;
} vsOut;

float wave(vec3 moveTo, float amplitude, float waveLength, float waveSpeed, out float dHeight_dx, out float dHeight_dz)
{
    const float frequency = 2.0 / waveLength;
    const float phase = waveSpeed * frequency;

    vec3 dir = moveTo - vec3(a_Position.x, 0.0, a_Position.z);
    float arg = dot(dir, vec3(a_Position.x, 0.0, a_Position.z) * frequency) + u_Time * phase;

    dHeight_dx = amplitude * frequency * dir.x * cos(arg);
    dHeight_dz = amplitude * frequency * dir.z * cos(arg);

    return sin(arg) * amplitude * waveLength;
}

void main()
{
    float dHeight_dx0, dHeight_dz0;
    float dHeight_dx1, dHeight_dz1;
    float dHeight_dx2, dHeight_dz2;
    float dHeight_dx3, dHeight_dz3;
    
    float h0 = wave(vec3(0.0, 0.0, 1.0), 0.1, 0.5, 1.0, dHeight_dx0, dHeight_dz0);
    float h1 = wave(vec3(0.0, 0.0, -1.0), 0.1, 0.3, 0.1, dHeight_dx1, dHeight_dz1);
    float h2 = wave(vec3(1.0, 0.0, 0.0), 0.05, 0.4, 0.2, dHeight_dx2, dHeight_dz2);
    float h3 = wave(vec3(0.0, 0.0, -1.0), 0.1, 0.6, 0.2, dHeight_dx3, dHeight_dz3);
    
    float heightSum = h0 + h1 + h2 + h3;
    float dHeight_dxSum = dHeight_dx0 + dHeight_dx1 + dHeight_dx2 + dHeight_dx3;
    float dHeight_dzSum = dHeight_dz0 + dHeight_dz1 + dHeight_dz2 + dHeight_dz3;

	vec4 vertexPosition = vec4(a_Position.x, heightSum, a_Position.z, 1.0);
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vertexPosition;

    vec3 normal = normalize(vec3(-dHeight_dxSum, 1.0, -dHeight_dzSum));
    vsOut.vs_Normal = mat3(transpose(inverse(u_ModelMatrix))) * normal;

	vsOut.vs_FragmentPosition = vec3(u_ModelMatrix * vertexPosition);
}