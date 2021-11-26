#version 430

layout (location = 0) in vec3 pos;
uniform int rotation_degrees;
uniform mat4 translation_matrix, projection_matrix;
out vec4 vColor;

mat4 RotateX(float rotation_radians)
{
    float s = sin(rotation_radians);
    float c = cos(rotation_radians);
    mat4 ret = mat4(
        1,  0,  0,  0,
        0,  c,  s,  0,
        0, -s,  c,  0,
        0,  0,  0,  1
    );
    return ret;
}

mat4 RotateY(float rotation_radians)
{
    float s = sin(rotation_radians);
    float c = cos(rotation_radians);
    mat4 ret = mat4(
        c,  0, -s,  0,
        0,  1,  0,  0,
        s,  0,  c,  0,
        0,  0,  0,  1
    );
    return ret;
}

mat4 RotateZ(float rotation_radians)
{
    float s = sin(rotation_radians);
    float c = cos(rotation_radians);
    mat4 ret = mat4(
         c,  s,  0,  0,
        -s,  c,  0,  0,
         0,  0,  1,  0,
         0,  0,  0,  1
    );
    return ret;
}

mat4 ScaleDown(float s)
{
    mat4 ret = mat4(
        s, 0, 0, 0,
        0, s, 0, 0,
        0, 0, s, 0,
        0, 0, 0, 1
    );
    return ret;
}

float DegreesToRadians() { return ((rotation_degrees * 3.1415) / 180); }

mat4 Spin(float radians) { return (RotateY(radians) * RotateZ(radians) * RotateX(radians)); }

void main()
{
    vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0);
    gl_Position = (ScaleDown(0.6f) * projection_matrix * translation_matrix * Spin(DegreesToRadians()) * vec4(pos, 1.0));
}