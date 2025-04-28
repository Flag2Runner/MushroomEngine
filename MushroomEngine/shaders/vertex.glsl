#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aVertexColor;

uniform mat4 modelMat;
uniform mat4 projectionMat;
uniform mat4 viewMat;

out vec3 vertexColor;

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
    vertexColor = aVertexColor;
}