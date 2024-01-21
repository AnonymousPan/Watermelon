#version 330 core
layout (location = 0) in vec4 VertexData;

out vec2 TexCoord;

uniform mat4 Uniform_Trans;

void main()
{
    gl_Position = Uniform_Trans * vec4(
        VertexData.xy,
        0.0f,
        1.0f
    );
    TexCoord = VertexData.zw;
}