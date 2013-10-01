#ifndef MESHRENDERER_H__
#define MESHRENDERER_H__
 
#include <string>
#include "Framework/OBJ/File.h"
#include "Framework/OBJ/Object.h"
#include "Framework/GL/Program.h"
#include "Framework/GL/VertexArray.h"
#include "Framework/APP/Camera.h"
#include "Framework/APP/IDrawable.h"

class MeshRenderer : public APP::IDrawable
{
    /*!
    ** GLData for the mesh loaded from an .obj file provided by [filename].
    */
    class GLMesh
    {
    public:
        GLMesh(const std::string& filename);
        ~GLMesh();

        GL::ArrayBufferSD* Positions;
        GL::ArrayBufferSD* TexCoords;
        GL::ArrayBufferSD* Normals;

        unsigned int NumVertices;
    };

public:
    MeshRenderer(const std::string& filename);
    ~MeshRenderer();

    virtual void Draw();
    virtual void OnCameraUpdate();

private: 
    void setUpGLData(const std::string& filename);

    GL::Program program_;
    GL::VertexArray vertexArray_;
    GL::BufferObject* buffer_;
    unsigned int numVertices_;
    OBJ::File* file_;

    GLMesh mesh_;
};
 
#endif /* end of include guard: MESHRENDERER_H__ */
