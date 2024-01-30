#version 330 core
layout (location = 0) in vec4 VertexData;

out vec2 TexCoord;

uniform mat4 Uniform_Trans;
uniform int Uniform_NumberIndex;

void main()
{
    gl_Position = Uniform_Trans * vec4(
        VertexData.xy,
        0.0f,
        1.0f
    );
    TexCoord = vec2(VertexData.z + Uniform_NumberIndex * 0.1f, VertexData.w);
}