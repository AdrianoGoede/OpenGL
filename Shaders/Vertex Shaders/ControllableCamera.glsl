#version 430

layout (location = 0) in vec3 pos;
uniform mat4 projectionMatrix, viewMatrix, translationMatrix;
out vec4 vColor;

void main()
{
    vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0);
    gl_Position = (projectionMatrix * viewMatrix * translationMatrix * vec4(pos, 1.0));
}