/*!
** A simple implemenation on how to render text in OpenGL using the freetype 
** library
**    
** @since 2013-09-13
*/
#ifndef TEXTRENDERER_H__
#define TEXTRENDERER_H__
 
#include "Framework/APP/IRenderer.h"
#include "Framework/GL/Program.h"
#include "Framework/GL/VertexArray.h"
#include "Framework/GL/BufferObject.h"
#include "Framework/APP/Camera.h"
#include "Framework/APP/ICameraObserver.h"

class TextRenderer : public APP::IRenderer
{
public:
    TextRenderer();
    ~TextRenderer();

    virtual void Render();

private:
    GL::Program program_;
    GL::VertexArray vertexArray_;
    GL::BufferObject bufferObject_;
};

#endif /* end of include guard: TEXTRENDERER_H__ */
