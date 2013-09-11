#version 150

out vec4 FragOutput;


in VertexShader
{
    vec3 Colors;
}
VertexShader;

void main()
{
    FragOutput = vec4(VertexShader.Colors, 1.0f);
}