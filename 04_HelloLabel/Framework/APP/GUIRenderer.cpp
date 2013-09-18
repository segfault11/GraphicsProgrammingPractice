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
    program_.BindAttribLocation(0, "PosData");
    program_.BindAttribLocation(1, "TexCoords");
    program_.BindFragDataLocation(0, "FragOutput");
    program_.Compile();

    // CONFIGURE IT ..
    program_.SetInt("ScreenWidth", APP::GetScreenWidth());
    program_.SetInt("ScreenHeight", APP::GetScreenHeight());
    program_.SetInt("GlyphHeight", atlas_->GetHeight());
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
    GLsizei size = sizeof(int)*2*length;

    int* posData = new int[2*length];
    float* texData = new float[2*length];
    int xOff = 0;

    for (unsigned int i = 0; i < length; i++)
    {
        int width = atlas_->GetCharWidth(text.c_str()[i]);
        int texOff = atlas_->GetCharOffset(text.c_str()[i]);
        posData[2*i + 0] = xOff;
        posData[2*i + 1] = width;
        texData[2*i + 0] = static_cast<float>(texOff)/atlas_->GetWidth();
        texData[2*i + 1] = static_cast<float>(texOff + width)/atlas_->GetWidth();
        xOff += width;
    }

    posBuffer_ = new GL::BufferObject(GL_ARRAY_BUFFER, size, GL_STATIC_DRAW);
    posBuffer_->SetData(size, posData);

    texBuffer_ = new GL::BufferObject(GL_ARRAY_BUFFER, size, GL_STATIC_DRAW);
    texBuffer_->SetData(size, texData);

    // ... AND ATTACH IT TO THE VERTEX ARRAY
    vertexArray_->SetAttribute(posBuffer_, 0, 2, GL_INT, GL_FALSE, 0, 0);
    vertexArray_->SetAttribute(texBuffer_, 1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    delete posData;

    // ... Set the origin of the label in the program
    program_.SetIVec2("Origin", ele.GetPosition());
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
