#ifndef MESHRENDERER_H__
#define MESHRENDERER_H__
 
#include <string>
#include "Framework/OBJ/File.h"
#include "Framework/GL/Program.h"
#include "Framework/GL/VertexArray.h"
#include "Framework/GL/Perspective.h"
#include "Framework/APP/Camera.h"
#include "Framework/APP/IDrawable.h"

class MeshRenderer : public APP::IDrawable
{
public:
    MeshRenderer(const std::string& filename);
    ~MeshRenderer();

    virtual void Draw();
    virtual void OnCameraUpdate();

private: 
    GL::Program program_;
    GL::VertexArray vertexArray_;
    GL::BufferObject* buffer_;
    OBJ::File* file_;

    GL::Perspective perspective_;
};
 
#endif /* end of include guard: MESHRENDERER_H__ */
