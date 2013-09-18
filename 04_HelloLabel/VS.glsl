#version 150

uniform ivec2 Origin;
uniform int ScreenWidth;
uniform int ScreenHeight;

in ivec2 PosData;  // x offset from the [Origin] and width of the glyph 
in vec2 TexCoords; // Texture x offsets (start and end) + position x-offset

out VertexData
{
    float GlyphWidthNDC;  // Glyph width in NDC
    float GlyphHeightNDC; // Glyph height in NDC
} 
VertexData;

void main()
{
    float posX = float(Origin.x + PosData.x)/ScreenWidth;
    float posY = float(Origin.y)/ScreenWidth;

    posX = 2.0f*posX - 1.0f;
    posY = 2.0f*posY - 1.0f;

    VertexData.GlyphWidthNDC = (float(PosData.y))/ScreenWidth;

    gl_Position = vec4(posX, posY, 0.0f, 1.0f);
}
