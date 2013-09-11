#version 150

in vec2 Position;
in vec3 Colors;

out VertexShader
{
    vec3 Colors;
}
VertexShader;

void main()
{
    VertexShader.Colors = Colors;
    gl_Position = vec4(Position, 0.0f, 1.0f);
}