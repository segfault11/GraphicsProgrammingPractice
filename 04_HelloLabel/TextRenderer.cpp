#include "TextRenderer.h"
//------------------------------------------------------------------------------
TextRenderer::TextRenderer()
: 
    bufferObject_(GL_ARRAY_BUFFER, 2*sizeof(float), GL_STATIC_DRAW)
{
    program_.AttachShader("TextVS.glsl", GL_VERTEX_SHADER);
    program_.AttachShader("TextGS.glsl", GL_GEOMETRY_SHADER);
    program_.AttachShader("TextFS.glsl", GL_FRAGMENT_SHADER);
    program_.BindAttribLocation(0, "Position");
    program_.BindFragDataLocation(0, "FragOut");
    program_.Compile();

    float data[] = {0.0f, 0.0f};
    bufferObject_.SetData(2*sizeof(float), data);

    vertexArray_.SetAttribute(&bufferObject_, 0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}
//------------------------------------------------------------------------------
TextRenderer::~TextRenderer()
{

}
//------------------------------------------------------------------------------
void TextRenderer::Render()
{
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    program_.Bind();
    vertexArray_.Bind();
    glDrawArrays(GL_POINTS, 0, 1);
}
//------------------------------------------------------------------------------
