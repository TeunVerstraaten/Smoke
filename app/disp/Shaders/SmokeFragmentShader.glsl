#version 430 core
in vec3 out_color;

out vec4 outColor;

uniform float time = 1;
uniform int width;
uniform int height;

void main()
{
    outColor = vec4(out_color, 1.0f);
}
