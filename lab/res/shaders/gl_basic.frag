#version 460 core

in VSOut
{
    vec2 textureCoordinate;
} fsIn;

out vec4 resultedColor;

uniform sampler2D u_DiffuseTexture1;

void main()
{
    vec4 texColor = texture(u_DiffuseTexture1, fsIn.textureCoordinate);
    if (texColor.a < 0.1)
    {
        discard;
    }
    
    resultedColor = texture(u_DiffuseTexture1, fsIn.textureCoordinate);
}