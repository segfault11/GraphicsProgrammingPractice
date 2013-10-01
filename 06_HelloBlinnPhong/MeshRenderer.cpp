#include "MeshRenderer.h"
#include <iostream>
#include "Framework/APP/Application.h"
//------------------------------------------------------------------------------
//                           PUBLIC DEFINITIONS
//------------------------------------------------------------------------------
MeshRenderer::MeshRenderer(const std::string& filename)
:
    APP::IDrawable(), mesh_(filename)
{
    program_.AttachShader("MeshVS.glsl", GL_VERTEX_SHADER);
    program_.AttachShader("MeshFS.glsl", GL_FRAGMENT_SHADER);
    program_.BindAttribLocation(0, "Position");
    program_.BindFragDataLocation(0, "FragColor");
    program_.Compile();
    program_.SetMat4("V", APP::GetCamera().GetData());
    program_.SetMat4("P", APP::GetCamera().GetPerspectiveData());

    vertexArray_.SetAttribute(mesh_.Positions, 0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
//------------------------------------------------------------------------------
MeshRenderer::~MeshRenderer()
{

}
//------------------------------------------------------------------------------
void MeshRenderer::Draw()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program_.Bind();
    vertexArray_.Bind();
    glDrawArrays(GL_TRIANGLES, 0, mesh_.NumVertices);
}
//------------------------------------------------------------------------------
void MeshRenderer::OnCameraUpdate()
{

}
//------------------------------------------------------------------------------
//                           PRIVATE DEFINITIONS
//------------------------------------------------------------------------------
void MeshRenderer::setUpGLData(const std::string& filename)
{
    const Obj::File* f = Obj::Load(filename, NULL);
    
    // compute total number of faces
    unsigned int numFaces = 0;

    for (unsigned int i = 0; i < f->Objects.size(); i++)
    {
        for (unsigned int j = 0; j < f->Objects[i].Groups.size(); j++)
        {
            numFaces += f->Objects[i].Groups[j].Faces.size();
        }
    }

    // allocate space for positions
    Math::Vector3F* pos = new Math::Vector3F[3*numFaces];

    ERROR_ASSERT(pos != NULL)

    // fill positions array from the .obj file
    unsigned int c = 0;

    for (unsigned int i = 0; i < f->Objects.size(); i++)
    {
        for (unsigned int j = 0; j < f->Objects[i].Groups.size(); j++)
        {
            for (unsigned int k = 0; k < f->Objects[i].Groups[j].Faces.size(); k++)
            {
                const Math::Tuple3UI& posIds = 
                    f->Objects[i].Groups[j].Faces[k].PositionIndices;
                
                pos[c + 0] = f->Positions[posIds[0]];
                pos[c + 1] = f->Positions[posIds[1]];
                pos[c + 2] = f->Positions[posIds[2]];

                c += 3;
            }
        }
    }

    // create GL buffer
    this->buffer_ = new GL::BufferObject(
            GL_ARRAY_BUFFER, 
            sizeof(Math::Vector3F)*3*numFaces, 
            GL_STATIC_DRAW
        );
    this->buffer_->SetData(
        sizeof(Math::Vector3F)*3*numFaces, 
        static_cast<const void*>(pos)
    );

    // set VAO
    this->vertexArray_.SetAttribute(this->buffer_, 0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // clean up
    delete[] pos;
    Obj::ReleaseFile(&f);

    // save # of vertices
    numVertices_ = 3*numFaces;
}
//------------------------------------------------------------------------------
MeshRenderer::GLMesh::GLMesh(const std::string& filename)
: 
    Positions(NULL), 
    TexCoords(NULL), 
    Normals(NULL),
    NumVertices(0)
{
    const Obj::File* f = Obj::Load(filename, NULL);
    
    // compute total number of faces
    unsigned int numFaces = 0;

    for (unsigned int i = 0; i < f->Objects.size(); i++)
    {
        for (unsigned int j = 0; j < f->Objects[i].Groups.size(); j++)
        {
            numFaces += f->Objects[i].Groups[j].Faces.size();
        }
    }

    // allocate space for positions
    Math::Vector3F* pos = new Math::Vector3F[3*numFaces];

    ERROR_ASSERT(pos != NULL)

    // fill positions array from the .obj file
    unsigned int c = 0;

    for (unsigned int i = 0; i < f->Objects.size(); i++)
    {
        for (unsigned int j = 0; j < f->Objects[i].Groups.size(); j++)
        {
            for (unsigned int k = 0; k < f->Objects[i].Groups[j].Faces.size(); k++)
            {
                const Math::Tuple3UI& posIds = 
                    f->Objects[i].Groups[j].Faces[k].PositionIndices;
                
                pos[c + 0] = f->Positions[posIds[0]];
                pos[c + 1] = f->Positions[posIds[1]];
                pos[c + 2] = f->Positions[posIds[2]];

                c += 3;
            }
        }
    }

    // create GL buffer
    this->Positions = new GL::ArrayBufferSD(sizeof(Math::Vector3F)*3*numFaces);
    this->Positions->SetData(
        sizeof(Math::Vector3F)*3*numFaces, 
        static_cast<const void*>(pos)
    );

    // clean up
    delete[] pos;
    Obj::ReleaseFile(&f);

    // save # of vertices
    this->NumVertices = 3*numFaces;    
}
//------------------------------------------------------------------------------
MeshRenderer::GLMesh::~GLMesh()
{
    if (this->Positions != NULL)
    {
        delete this->Positions;
    }

    if (this->TexCoords != NULL)
    {
        delete this->TexCoords;
    }

    if (this->Normals != NULL)
    {
        delete this->Normals;
    }
}
//------------------------------------------------------------------------------