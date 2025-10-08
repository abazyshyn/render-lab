#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat3  u_NormalMatrix;
uniform mat4  u_ModelMatrix;
uniform mat4  u_ViewMatrix;
uniform mat4  u_ProjectionMatrix;
uniform float u_Time;

out VSOut
{
    vec3 vs_Normal;
	vec3 vs_FragmentPosition;
} vsOut;

float wave(float amplitude, float waveLength, float waveSpeed, vec3 moveTo, out float partialDvx)
{
	const float frequency = 2 / waveLength;
	const float phase = waveSpeed * frequency; // Keep speed as a phase constant

	vec3 directionVector = moveTo - vec3(a_Position.x, 0.0, a_Position.z);
	float arg = dot(directionVector, vec3(a_Position.x, 0.0, a_Position.z) * frequency) + u_Time * phase;
	float height = sin(arg) * amplitude * waveLength; // Calculate wave on the xz plane

	partialDvx = frequency * directionVector.x * amplitude * cos(arg);

	return height;
}

void main()
{
    // Calculate different waves and apply "Sum of sines"
	float partialDvx0, partialDvx1, partialDvx2, partialDvx3;
	float sin0 = wave(0.1, 0.5, 0.5, vec3(0.0, 0.0, 1.0), partialDvx0);
    float sin1 = wave(0.1, 0.3, 0.1, vec3(0.0, 0.0, -1.0), partialDvx1);
	float sin2 = wave(0.05, 0.4, 0.2, vec3(1.0, 0.0, 0.0), partialDvx2);
    float sin3 = wave(0.1, 0.6, 0.2, vec3(0.0, 0.0, -1.0), partialDvx3);
	float sinSum = sin0 + sin1 + sin2 + sin3;
	float partialDvxSum = partialDvx0 + partialDvx1 + partialDvx2 + partialDvx3;

	vec4 vertexPosition = vec4(a_Position.x, sinSum, a_Position.z, 1.0);
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vertexPosition;

    vec3 binormalVector = vec3(1.0, 0.0, partialDvxSum);
	vec3 tangentVector = vec3(0.0, 1.0, partialDvxSum);
	vsOut.vs_Normal = cross(binormalVector, tangentVector) * u_NormalMatrix;
	vsOut.vs_FragmentPosition = vec3(vertexPosition * u_ModelMatrix * u_ViewMatrix);
}