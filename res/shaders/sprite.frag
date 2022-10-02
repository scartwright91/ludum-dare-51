#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D u_Texture;
uniform bool u_UseTexture;

uniform vec3 u_SpriteColor;
uniform float u_Alpha;

void main()
{    
    if (u_UseTexture)
        color = texture(u_Texture, TexCoords) * vec4(1, 1, 1, u_Alpha);
    else
        color = vec4(u_SpriteColor, u_Alpha);
}
