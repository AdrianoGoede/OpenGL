#version 430

layout (location = 0) in vec3 pos;
uniform float rotationRadians;
uniform mat4 translationMatrix, projectionMatrix;
out vec4 vColor;

mat4 RotateX(float s, float c)
{
    return mat4(
        1,  0,  0,  0,
        0,  c,  s,  0,
        0, -s,  c,  0,
        0,  0,  0,  1
    );
}

mat4 RotateY(float s, float c)
{
    return mat4(
        c,  0, -s,  0,
        0,  1,  0,  0,
        s,  0,  c,  0,
        0,  0,  0,  1
    );
}

mat4 RotateZ(float s, float c)
{
    return mat4(
         c,  s,  0,  0,
        -s,  c,  0,  0,
         0,  0,  1,  0,
         0,  0,  0,  1
    );
}

mat4 Scale(float s)
{
    return mat4(
        s, 0, 0, 0,
        0, s, 0, 0,
        0, 0, s, 0,
        0, 0, 0, 1
    );
}

mat4 Spin() 
{ 
    float s = sin(rotationRadians);
    float c = cos(rotationRadians);
    return (RotateY(s, c) * RotateZ(s, c) * RotateX(s, c)); 
}

void main()
{
    vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0);
    gl_Position = (Scale(0.6f) * projectionMatrix * translationMatrix * Spin() * vec4(pos, 1.0));
}