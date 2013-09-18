#version 150

out VertexData
{
    flat float GlyphWidthNDC;  // Glyph width in NDC
    flat float GlyphHeightNDC; // Glyph height in NDC
} 
VertexIn;

layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

void main()
{
    vec4 pos = gl_in[0].gl_Position;
    float w = VertexIn.GlyphWidthNDC;
    float h = VertexIn.GlyphHeightNDC;

    gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
    EmitVertex(); 

    gl_Position = vec4(pos.x + w, pos.y, 0.0f, 1.0f);
    EmitVertex(); 

    gl_Position = vec4(pos.x + w, pos.y + h, 0.0f, 1.0f);
    EmitVertex(); 
}