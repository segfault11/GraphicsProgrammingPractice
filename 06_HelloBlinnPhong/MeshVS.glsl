#version 150

uniform mat4 V;
uniform mat4 P;
uniform vec3 Ambient;

in vec3 Position;

void main()
{
    gl_Position = P*V*vec4(Position, 1.0f);
}