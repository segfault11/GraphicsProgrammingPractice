#include "UserInterface.h"
#include "../APP/Application.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../../SOIL.h"
#include <iostream>
#include <cmath>
#include "../GL/Program.h"

//------------------------------------------------------------------------------
//                           PRIVATE DECLARATIONS
//------------------------------------------------------------------------------

static FT_Library library_;
static GL::VertexArray* vertexArray_ = NULL;
static GL::Program* program_;

static struct
{
    GL::Texture2DA* Atlas;
    int Width;
    int Height;
} 
atlas_;

static struct 
{
    int Width;  // width of the character in pixel
    int XOff0;  // x offset in the atlas to the start of the character in pixel
} 
characterInfo_[128];

struct LabelData
{
    const UI::Label* Label;
    GL::BufferObject* BufferObject;

    LabelData(const UI::Label* label, GL::BufferObject* bufferObject)
    :
        Label(label),
        BufferObject(bufferObject)
    {}

    LabelData(const LabelData& orig)
    :
        Label(orig.Label),
        BufferObject(orig.BufferObject)
    {}
    
};
static std::list<LabelData> labels_;

static void createAtlasData(const std::string &font, unsigned int fontSize);
static void createProgram();

//------------------------------------------------------------------------------
//                           PUBLIC DEFINITIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void UI::Init(const std::string &font, unsigned int fontSize)
{
    createAtlasData(font, fontSize);
    createProgram();
}
//------------------------------------------------------------------------------
void UI::Destroy()
{
    delete atlas_.Atlas;
    delete vertexArray_;
}
//------------------------------------------------------------------------------
void UI::AddLabel(const UI::Label& label)
{
    GL::BufferObject* buffer = new GL::BufferObject(
        GL_ARRAY_BUFFER, 
        label.GetLength()*sizeof(float)*3, 
        GL_STATIC_DRAW
    );

    float* data = new float[3*label.GetLength()];

    std::string text = label.GetText();

    int xOffset = 0;
    for (unsigned int i = 0; i < label.GetLength(); i++)
    {   
        data[3*i + 0]  = static_cast<float>(characterInfo_[i].XOff0)/atlas_.Width;
        data[3*i + 1]  = static_cast<float>(characterInfo_[i].XOff0 + characterInfo_[i].Width)/atlas_.Width;
        data[3*i + 2]  = static_cast<float>(xOffset);
        xOffset += characterInfo_[i].Width;
    }

    buffer->SetData(label.GetLength()*sizeof(float)*3, data);

    labels_.push_back(LabelData(&label, buffer));

    delete[] data;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                           PRIVATE DEFINITIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void createAtlasData(const std::string &font, unsigned int fontSize)
{
    // INIT FREETYPE AND CREATE FONT ATLAS

    ERROR_ASSERT(APP::IsInitialized())

    // load the library
    FT_Error err = FT_Init_FreeType(&library_);

    ERROR_ASSERT(err == 0)

    FT_Face face;

    // load the font (face)
    err = FT_New_Face(
            library_,
            font.c_str(),
            0,
            &face 
        );

    ERROR_ASSERT(err == 0)

    FT_Set_Pixel_Sizes(face, 0, fontSize);    

    FT_GlyphSlot g = face->glyph;
    int atlasWidth = 0;
    int atlasHeight = 0;
    int blMin = 0;
    int blMax = -1;
    
    // compute the dimensions of the atlas
    for (unsigned int i = 32; i < 128; i++) 
    {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) 
        {
            ERROR_WARNING("Loading character %c failed!")
            continue;
        }
        
        atlasWidth += (g->bitmap.width + std::abs(g->bitmap_left));
        blMin = std::min(blMin, g->bitmap_top);

        if (g->bitmap_top > 0)
        {
            blMin = std::min(blMin, g->bitmap_top - g->bitmap.rows);
        }

        blMax = std::max(blMax, g->bitmap_top);

        atlasHeight = std::max(atlasHeight, g->bitmap.rows);
    }

    atlasHeight = blMax - blMin;

    int baseline = 0 - blMin;
    unsigned char* atlas = new unsigned char[atlasWidth*atlasHeight];
    int marker = 0;
    
    for (unsigned int i = 32; i < 128; i++) 
    {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) 
        {
            continue;
        }
        
        int w = g->bitmap.width;
        int h = g->bitmap.rows;
        
        unsigned char* buffer = g->bitmap.buffer;
        
        // copy character to atlas
        for (unsigned int v = 0; v < h; v++)
        {
            for (unsigned int u = 0; u < w; u++)
            {
                int y = atlasHeight - (baseline + g->bitmap_top) + v;
                int x = marker + u  + std::abs(g->bitmap_left);
                atlas[y*atlasWidth + x] = buffer[v*w + u];
            }
        }

        // save character info
        characterInfo_[i].Width = w + std::abs(g->bitmap_left);
        characterInfo_[i].XOff0 = marker;

        // increase marker
        marker += (w + std::abs(g->bitmap_left));
    }

    // initialize the atlas
    atlas_.Atlas = new GL::Texture2DA(
        atlasWidth, 
        atlasHeight, 
        static_cast<void*>(atlas)
    );

    atlas_.Width = atlasWidth;
    atlas_.Height = atlasHeight;

    vertexArray_ = new GL::VertexArray();
    
    // clean up
    delete[] atlas;
    FT_Done_FreeType(library_);
}
//------------------------------------------------------------------------------
#include "Shader.inl"
void createProgram()
{
    program_ = new GL::Program();
    program_->AttachShaderFromSource(UI::VertexShader, GL_VERTEX_SHADER);
    program_->AttachShaderFromSource(UI::FragmentShader, GL_FRAGMENT_SHADER);
    program_->BindAttribLocation(0, "Data");
    program_->BindFragDataLocation(0, "FragOutput");
    program_->Compile();
}
//------------------------------------------------------------------------------
