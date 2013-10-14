#version 150

out vec4 FragOutput;
in vec3 Color;

void main()
{
    FragOutput = vec4(Color, 1.0f);
}