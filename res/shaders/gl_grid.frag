#version 460 core

in vec3 curGridVertexWorldPos;

uniform float u_GridCellSize              = 0.025;
uniform float u_GridSize                  = 100.0;
uniform float u_GridMinPixelsBetweenCells = 2.0;
uniform vec4  u_GridColorThin             = vec4(0.5, 0.5, 0.5, 1.0);
uniform vec4  u_GridColorThick            = vec4(0.0, 0.0, 0.0, 1.0);
uniform vec3  u_CameraWorldPos;

out vec4 resultColor;

float max2(vec2 v) { return max(v.x, v.y); }

vec2 satv(vec2 v) { return clamp(v, vec2(0.0), vec2(1.0)); }

float satf(float x) { return clamp(x, 0.0, 1.0); }

float log10(float x) { return log(x) / log(10.0); }

void main()
{
    vec2 dvx = vec2(dFdx(curGridVertexWorldPos.x), dFdy(curGridVertexWorldPos.x));
    vec2 dvy = vec2(dFdx(curGridVertexWorldPos.z), dFdy(curGridVertexWorldPos.z));

    float lengthX = length(dvx);
    float lengthY = length(dvy);
    
    vec2 dudv = vec2(lengthX, lengthY);

    float lod = max(0.0, log10(length(dudv) * u_GridMinPixelsBetweenCells / u_GridCellSize) + 1.0);
    float gridCellSizeLod0 = u_GridCellSize * pow(10.0, floor(lod));
    float gridCellSizeLod1 = gridCellSizeLod0 * 10.0;
    float gridCellSizeLod2 = gridCellSizeLod1 * 10.0;

    dudv *= 4.0;

    vec2 modDiv_dudv = mod(curGridVertexWorldPos.xz, gridCellSizeLod0) / dudv;
    float lod0a = max2(vec2(1.0) - abs(satv(modDiv_dudv) * 2.0 - vec2(1.0)));

    modDiv_dudv = mod(curGridVertexWorldPos.xz, gridCellSizeLod1) / dudv;
    float lod1a = max2(vec2(1.0) - abs(satv(modDiv_dudv) * 2.0 - vec2(1.0)));

    modDiv_dudv = mod(curGridVertexWorldPos.xz, gridCellSizeLod2) / dudv;
    float lod2a = max2(vec2(1.0) - abs(satv(modDiv_dudv) * 2.0 - vec2(1.0)));

    float lod_fade = fract(lod);

    vec4 color;

    if (lod2a > 0.0)
    {
        color = u_GridColorThick;
        color.a *= lod2a;
    }
    else
    {
        if (lod1a > 0.0)
        {
            color = mix(u_GridColorThick, u_GridColorThin, lod_fade);
            color.a *= lod1a;
        }
        else
        {
            color = u_GridColorThin;
            color.a *= lod0a * (1.0 - lod_fade);
        }
    }

    float opacityFalloff = (1.0 - satf(10.0 * length(curGridVertexWorldPos.xz - u_CameraWorldPos.xz) / u_GridSize));
    color.a *= opacityFalloff;

    resultColor = color;
}
