#version 460 core

uniform vec3 u_CameraPosition;
uniform samplerCube skybox;

in VSOut
{
    vec3 position;
    vec3 normal;
} fsIn;

out vec4 resultedColor;

void main()
{
    float airToIce = 1.0 / 1.309;
    vec3 cameraDirection = normalize(fsIn.position - u_CameraPosition);
    vec3 reflectedCameraDirection = refract(cameraDirection, normalize(fsIn.normal), airToIce);

    resultedColor = vec4(texture(skybox, reflectedCameraDirection).rgb, 1.0);
}