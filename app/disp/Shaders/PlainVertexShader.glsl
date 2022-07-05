#version 430 core
in vec2 position;
in vec3 color;

out vec3 Color;

uniform float zoom = 1.0;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0 / zoom);
    Color = color;
}
