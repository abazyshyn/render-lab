#version 460 core

uniform vec3 u_CameraPosition;
uniform samplerCube skybox;

in vec3 position;
in vec3 normal;
out vec4 resultedColor;

void main()
{
    float airToIce = 1.0 / 1.309;
    vec3 cameraDirection = normalize(position - u_CameraPosition);
    vec3 reflectedCameraDirection = refract(cameraDirection, normalize(normal), airToIce);

    resultedColor = vec4(texture(skybox, reflectedCameraDirection).rgb, 1.0);
}