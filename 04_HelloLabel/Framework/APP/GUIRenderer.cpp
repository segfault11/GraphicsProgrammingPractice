#include "GUIRenderer.h"
#include "Shader.h"
#include "Application.h"
#include <iostream>
#include "../../SOIL.h"
//------------------------------------------------------------------------------
APP::GUIRenderer::GUIRenderer(const TextureAtlas& atlas)
:
    atlas_(&atlas)
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
}
//------------------------------------------------------------------------------
APP::GUIRenderer::~GUIRenderer()
{
    std::list<GUIElementInfo>::iterator i = guiElements_.begin();
    std::list<GUIElementInfo>::iterator end = guiElements_.end();

    for (; i != end; i++)
    {
        delete (*i).VertexArray;
        delete (*i).BufferObject;
    }
}
//------------------------------------------------------------------------------
void APP::GUIRenderer::RegisterGUIElement(const GUIElement& ele)
{
    // CREATE A VERTEX OBJ AND BUFFER OBJECT FOR THE GUI ELEMENT AND SAVE 
    // IT WITH THEM TO A LIST.

    GUIElementInfo eleInfo;

    eleInfo.VertexArray = new GL::VertexArray();
    eleInfo.GUIElement = &ele;

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

    eleInfo.BufferObject = new GL::BufferObject(
            GL_ARRAY_BUFFER, 
            size, 
            GL_STATIC_DRAW
        );
    eleInfo.BufferObject->SetData(size, glyphData);

    // ... AND ATTACH IT TO THE VERTEX ARRAY
    eleInfo.VertexArray->SetAttribute(
        eleInfo.BufferObject, 
        0, 4, GL_INT, GL_FALSE, 
        0, 0
    );

    delete[] glyphData;

    // SAVE ELEMENT INFO TO LIST
    guiElements_.push_back(eleInfo);

}
//------------------------------------------------------------------------------
void APP::GUIRenderer::Render()
{
    program_.Bind();
    atlas_->Bind(1);

    std::list<GUIElementInfo>::iterator i = guiElements_.begin();
    std::list<GUIElementInfo>::iterator end = guiElements_.end();

    for (; i != end; i++)
    {
        program_.SetVec3("TextColor", (*i).GUIElement->GetTextColor());
        (*i).VertexArray->Bind();
        glDrawArrays(GL_POINTS, 0, (*i).GUIElement->GetText().size());
    }

}
//------------------------------------------------------------------------------
