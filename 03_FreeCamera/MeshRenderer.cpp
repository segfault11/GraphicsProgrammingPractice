#include "MeshRenderer.h"
#include <iostream>
#include "Framework/SDL/Application.h"
//------------------------------------------------------------------------------
MeshRenderer::MeshRenderer(const std::string& filename, SDL::Camera& camera)
:
    IRenderer(camera),
    perspective_(60.0f, 1.0f, 0.001f, 1.0f)
{
    program_.AttachShader("MeshVS.glsl", GL_VERTEX_SHADER);
    program_.AttachShader("MeshFS.glsl", GL_FRAGMENT_SHADER);
    program_.BindAttribLocation(0, "Position");
    program_.BindFragDataLocation(0, "FragColor");
    program_.Compile();
    program_.SetMat4("V", camera_->GetData());
    program_.SetMat4("P", perspective_.GetData());

    std::cout << camera_->ToString() << std::endl;

    file_ = new OBJ::File(filename.c_str());
    const OBJ::Mesh& mesh = file_->GetMesh();

    buffer_.SetData(
        GL_ARRAY_BUFFER, 
        mesh.GetNumVertices()*sizeof(Math::Vector3F), 
        mesh.GetPositionData(), 
        GL_STATIC_DRAW
    );

    vertexArray_.SetAttribute(&buffer_, 0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
//------------------------------------------------------------------------------
MeshRenderer::~MeshRenderer()
{

}
//------------------------------------------------------------------------------
void MeshRenderer::Render()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program_.Bind();
    vertexArray_.Bind();
    glDrawArrays(GL_TRIANGLES, 0, file_->GetMesh().GetNumVertices());
}
//------------------------------------------------------------------------------
void MeshRenderer::OnCameraUpdate()
{
    program_.SetMat4("V", camera_->GetData());
}
//------------------------------------------------------------------------------

