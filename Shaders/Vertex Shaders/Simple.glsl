#version 430

layout (location = 0) in vec3 pos;
uniform mat4 translationMatrix, projectionMatrix;

void main()
{
    gl_Position = vec4(pos, 1.0);
}