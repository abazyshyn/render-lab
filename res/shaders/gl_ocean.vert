#version 460 core

layout(location = 0) in vec3 a_Position;

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

float wave(float amplitude, float waveLength, float waveSpeed, out float dvx, out float dvz)
{
	float freq = 2 / waveLength;
	float phase = waveSpeed * freq;

	float arg = a_Position.x * freq + a_Position.z * freq + u_Time * phase;
	float height = sin(arg) * amplitude * waveLength; // Calculate wave on the xz plane

	dvx = cos(arg) * amplitude * waveLength;
	dvz = dvx; // Same "arg" same formula

	return height;
}

void main()
{
    // Calculate different waves and apply "Sum of sines"
	float dvx0, dvx1, dvx2, dvz0, dvz1, dvz2; 
	float sin0 = wave(0.1, 0.5, 0.5, dvx0, dvz0);
	float sin1 = wave(0.1, 0.1, 0.1, dvx1, dvz1);
	float sin2 = wave(0.1, 0.4, 0.2, dvx2, dvz2);
	
	float height = sin0 + sin1 + sin2;
	float dHdX = dvx0 + dvx1 + dvx2;
	float dHdZ = dvz0 + dvz1 + dvz2;

	vec4 vertexPosition = vec4(a_Position.x, height, a_Position.z, 1.0);

	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vertexPosition;

	vec3 tangentVector = vec3(1.0, 0.0, dHdX);
	vec3 binormalVector = vec3(0.0, 1.0, dHdZ);
	vec3 normal = normalize(cross(tangentVector, binormalVector));
	vsOut.vs_Normal = normalize(normal * u_NormalMatrix);
	vsOut.vs_FragmentPosition = vec3(vertexPosition * u_ModelMatrix * u_ViewMatrix);
}