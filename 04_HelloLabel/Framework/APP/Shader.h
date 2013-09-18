/*!
** Implementation of the shaders used by the GUI
**    
** @since 2013-09-16 
*/
#define TO_STRING(x) #x 


// namespace APP
// {
//------------------------------------------------------------------------------
    const char* VertexShader = 
    "#version 150\n"
    TO_STRING(
    uniform ivec2 Origin;
    uniform int ScreenWidth;
    uniform int ScreenHeight;
    uniform int GlyphHeight;

    in ivec2 PosData;  // x offset from the [Origin] and width of the glyph 
    in vec2 TexCoords; // Texture x offsets (start and end)

    out VertexData
    {
        float GlyphWidthNDC;  // Glyph width in NDC
        float GlyphHeightNDC; // Glyph height in NDC
        float TexStart;
        float TexEnd;        
    } 
    VertexOut;

    void main()
    {
        float posX = float(Origin.x + PosData.x)/ScreenWidth;
        float posY = float(Origin.y)/ScreenHeight;

        posX = 2.0f*posX - 1.0f;
        posY = 2.0f*posY - 1.0f;

        VertexOut.TexStart = TexCoords.x;
        VertexOut.TexEnd = TexCoords.y;

        VertexOut.GlyphWidthNDC = 2.0f*float(PosData.y)/ScreenWidth;
        VertexOut.GlyphHeightNDC = 2.0f*float(GlyphHeight)/ScreenHeight;



        gl_Position = vec4(posX, posY, 0.0f, 1.0f);
    }
    );
//------------------------------------------------------------------------------
    const char* GeometryShader = 
    "#version 150\n"
    TO_STRING(
    in VertexData
    {
        float GlyphWidthNDC;  // Glyph width in NDC
        float GlyphHeightNDC; // Glyph height in NDC
        float TexStart;
        float TexEnd;           
    } 
    VertexIn[];

    out VertexData
    {
        vec2 TexCoord;        
    } 
    VertexOut;    

    layout (points) in;
    layout (triangle_strip, max_vertices = 6) out;

    void main()
    {
        vec4 pos = gl_in[0].gl_Position;
        float w = VertexIn[0].GlyphWidthNDC;
        float h = VertexIn[0].GlyphHeightNDC;
        float ts = VertexIn[0].TexStart;
        float te = VertexIn[0].TexEnd;


        gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(ts, 1.0f);
        EmitVertex(); 

        gl_Position = vec4(pos.x + w, pos.y, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(te, 1.0f);
        EmitVertex(); 

        gl_Position = vec4(pos.x + w, pos.y + h, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(te, 0.0f);
        EmitVertex();
        EndPrimitive();  

        gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(ts, 1.0f);
        EmitVertex(); 

        gl_Position = vec4(pos.x, pos.y + h, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(ts, 0.0f);
        EmitVertex();

        gl_Position = vec4(pos.x + w, pos.y + h, 0.0f, 1.0f);
        VertexOut.TexCoord = vec2(te, 0.0f);
        EmitVertex(); 

        EndPrimitive();         
    }
    );

//------------------------------------------------------------------------------
    const char* FragmentShader = 
    "#version 150\n"
    TO_STRING(

    uniform sampler2D Atlas;

    in VertexData
    {
        vec2 TexCoord;        
    } 
    VertexIn; 
    
    out vec4 FragOut;

    void main()
    {
        vec4 t = texture(Atlas, VertexIn.TexCoord);

        FragOut = vec4(t.r, t.r, t.r, 1.0f);
    }
    );
//------------------------------------------------------------------------------
// }
