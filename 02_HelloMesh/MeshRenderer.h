#ifndef MESHRENDERER_H__
#define MESHRENDERER_H__
 
#include <string>
#include "Framework/OBJ/File.h"
#include "Framework/GL/Program.h"
#include "Framework/IDrawable.h"
#include "Framework/GL/VertexArray.h"
#include "Framework/GL/Perspective.h"
#include "Framework/GL/Camera.h"

class MeshRenderer : public IDrawable
{
public:
    MeshRenderer(const std::string& filename);
    ~MeshRenderer();

    void Draw() const;

private: 
    GL::Program program_;
    GL::VertexArray vertexArray_;
    GL::BufferObject buffer_;
    OBJ::File* file_;

    GL::Perspective perspective_;
    GL::Camera camera_;
};
 
#endif /* end of include guard: MESHRENDERER_H__ */