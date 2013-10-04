#version 150

in vec2 Position;
in vec3 Colors;

out vec3 Color;

void main()
{
    Color = Colors;
    gl_Position = vec4(Position, 0.0f, 1.0f);
}