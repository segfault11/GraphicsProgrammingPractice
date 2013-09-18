#include "GUIRenderer.h"
#include "Shader.h"
#include "Application.h"
#include <iostream>
#include "../../SOIL.h"
//------------------------------------------------------------------------------
APP::GUIRenderer::GUIRenderer(const TextureAtlas& atlas)
:
    atlas_(&atlas), posBuffer_(NULL), texBuffer_(NULL)
{
    // CREATE PROGRAM ...
    program_.AttachShaderFromSource(VertexShader, GL_VERTEX_SHADER);
    program_.AttachShaderFromSource(GeometryShader, GL_GEOMETRY_SHADER);
    program_.AttachShaderFromSource(FragmentShader, GL_FRAGMENT_SHADER);
    program_.BindAttribLocation(0, "GlyphData");
    program_.BindFragDataLocation(0, "FragOutput");
    program_.Compile();

    // CONFIGURE IT ..
    program_.SetInt("ScreenWidth", APP::GetScreenWidth());
    program_.SetInt("ScreenHeight", APP::GetScreenHeight());
    program_.SetInt("AtlasHeight", atlas_->GetHeight());
    program_.SetInt("AtlasWidth", atlas_->GetWidth());
    program_.SetInt("Atlas", 1);

    // CREATE VERTEX ARRAY  
    vertexArray_ = new GL::VertexArray();
}
//------------------------------------------------------------------------------
APP::GUIRenderer::~GUIRenderer()
{
    if (posBuffer_ != NULL)
    {
        delete posBuffer_;
    }

    if (texBuffer_ != NULL)
    {
        delete texBuffer_;
    }    

    delete vertexArray_;
}
//------------------------------------------------------------------------------
void APP::GUIRenderer::RegisterGUIElement(const GUIElement& ele)
{
    element_ = &ele;

    // CREATE BUFFER OBJECT FOR THE GUI ELEMENT ...
    std::string text = ele.GetText();  
    unsigned int length = text.size();
    GLsizei size = sizeof(int)*4*length;
    int* glyphData = new int[4*length];
    int posX = ele.GetPosition().GetX();
    int posY = ele.GetPosition().GetY();

    for (unsigned int i = 0; i < length; i++)
    {
        char c = text.c_str()[i];
        glyphData[4*i + 0] = posX + atlas_->GetBearing(c).GetX();
        glyphData[4*i + 1] = posY + atlas_->GetBearing(c).GetY();
        glyphData[4*i + 2] = atlas_->GetBitmapWidth(c);
        glyphData[4*i + 3] = atlas_->GetAtlasOffX(c);
        posX += atlas_->GetAdvance(c).GetX();
        posY += atlas_->GetAdvance(c).GetY();
    }

    posBuffer_ = new GL::BufferObject(GL_ARRAY_BUFFER, size, GL_STATIC_DRAW);
    posBuffer_->SetData(size, glyphData);

    // ... AND ATTACH IT TO THE VERTEX ARRAY
    vertexArray_->SetAttribute(posBuffer_, 0, 4, GL_INT, GL_FALSE, 0, 0);

    delete[] glyphData;

    // ... SET TEXT COLOR
    program_.SetVec3("TextColor", ele.GetTextColor());
}
//------------------------------------------------------------------------------
void APP::GUIRenderer::Render()
{
    program_.Bind();
    vertexArray_->Bind();
    atlas_->Bind(1);
    glDrawArrays(GL_POINTS, 0, element_->GetText().size());
}
//------------------------------------------------------------------------------
