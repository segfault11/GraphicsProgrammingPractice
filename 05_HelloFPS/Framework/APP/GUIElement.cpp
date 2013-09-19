//------------------------------------------------------------------------------
#include "GUIElement.h"
#include "Shader.h"
#include "Application.h"
#include <iostream>
#include "../../SOIL.h"
//------------------------------------------------------------------------------
APP::GUIElement::GUIElement(
    const std::string& text, 
    const Math::Vector2I& pos,
    const TextureAtlas& atlas
)
:
    atlas_(&atlas), text_(text), position_(pos)
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

    // CREATE A VERTEX OBJ AND BUFFER OBJECT FOR THE GUI ELEMENT AND SAVE 
    // IT WITH THEM TO A LIST.

    vertexArray_ = new GL::VertexArray();

    // CREATE BUFFER OBJECT FOR THE GUI ELEMENT ...
    unsigned int length = text_.size();
    GLsizei size = sizeof(int)*4*length;
    int* glyphData = new int[4*length];
    int posX = position_.GetX();
    int posY = position_.GetY();

    for (unsigned int i = 0; i < length; i++)
    {
        char c = text_.c_str()[i];
        glyphData[4*i + 0] = posX + atlas_->GetBearing(c).GetX();
        glyphData[4*i + 1] = posY + atlas_->GetBearing(c).GetY();
        glyphData[4*i + 2] = atlas_->GetBitmapWidth(c);
        glyphData[4*i + 3] = atlas_->GetAtlasOffX(c);
        posX += atlas_->GetAdvance(c).GetX();
        posY += atlas_->GetAdvance(c).GetY();
    }

    bufferObject_ = new GL::BufferObject(
            GL_ARRAY_BUFFER, 
            size, 
            GL_STATIC_DRAW
        );
    bufferObject_->SetData(size, glyphData);

    // ... AND ATTACH IT TO THE VERTEX ARRAY
    vertexArray_->SetAttribute(
        bufferObject_, 
        0, 4, GL_INT, GL_FALSE, 
        0, 0
    );

    delete[] glyphData;
}
//------------------------------------------------------------------------------
APP::GUIElement::~GUIElement()
{
        delete vertexArray_;
        delete bufferObject_;
}
//------------------------------------------------------------------------------
void APP::GUIElement::Draw()
{
    program_.Bind();
    atlas_->Bind(1);

    program_.SetVec3("TextColor", textColor_);
    vertexArray_->Bind();
    glDrawArrays(GL_POINTS, 0, text_.size());
}
//------------------------------------------------------------------------------
