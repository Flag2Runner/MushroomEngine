#version 460 core

out vec3 fragColor;

in vec3 vertexColor;

void main()
{
    fragColor = vertexColor;
}