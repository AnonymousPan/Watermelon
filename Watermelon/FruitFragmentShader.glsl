#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Texture;
uniform vec4 Uniform_Color;

void main()
{
    FragColor = texture(Texture, TexCoord) * Uniform_Color;
}