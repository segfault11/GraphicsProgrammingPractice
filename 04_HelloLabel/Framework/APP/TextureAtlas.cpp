#include "TextureAtlas.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <cmath>
#include "../GL/Program.h"
#include "Application.h"
//------------------------------------------------------------------------------
APP::TextureAtlas::TextureAtlas(const std::string& font, unsigned int fontSize)
{
    // INIT FREETYPE AND CREATE FONT ATLAS

    // check if we have and OpenGL context
    ERROR_ASSERT(APP::IsInitialized())

    FT_Library library;

    // load the library
    FT_Error err = FT_Init_FreeType(&library);

    ERROR_ASSERT(err == 0)

    FT_Face face;

    // load the font (face)
    err = FT_New_Face(
            library,
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
        
        if (i == 32)
        {
            std::cout << g->bitmap.width << std::endl;
            std::cout << g->bitmap_left << std::endl;
        }

        atlasWidth += (g->bitmap.width + (g->bitmap_left));
        blMin = std::min(blMin, g->bitmap_top);

        if (g->bitmap_top > 0)
        {
            blMin = std::min(blMin, g->bitmap_top - g->bitmap.rows);
        }

        blMax = std::max(blMax, g->bitmap_top);

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
                int x = marker + u  + (g->bitmap_left);
                atlas[y*atlasWidth + x] = buffer[v*w + u];
            }
        }

        // save character info
        charWidth_[i]  = w + (g->bitmap_left);
        charOffset_[i] = marker;

        // increase marker
        marker += (w + (g->bitmap_left));
    }

    // initialize member
    atlas_ = new GL::Tex2DR8FR8UI(
            atlasWidth, 
            atlasHeight, 
            static_cast<void*>(atlas)
        );   

    atlas_->SaveToBMP("test.bmp");

    width_ = atlasWidth;
    height_ = atlasHeight;

    // clean up
    delete[] atlas;
    FT_Done_FreeType(library);
}
//------------------------------------------------------------------------------
APP::TextureAtlas::~TextureAtlas()
{
    delete atlas_;
}
//------------------------------------------------------------------------------
void APP::TextureAtlas::Bind(int i) const
{
    atlas_->Bind(i);
}
//------------------------------------------------------------------------------
void APP::TextureAtlas::SaveToBMP(const std::string& filename) const
{
    atlas_->SaveToBMP(filename);
}
