#include "Triangle.h"
#include <GL/GLEW.h>
#include <iostream>

Triangle::Triangle()
{
    program_ = new Program();
    program_->AttachShader("TriangleVS.glsl", GL_VERTEX_SHADER);
    program_->AttachShader("TriangleFS.glsl", GL_FRAGMENT_SHADER);
    program_->BindAttribLocation(0, "Position");
    program_->BindAttribLocation(1, "Colors");
    program_->BindFragDataLocation(0, "FragOutput");
    program_->Compile();

    float positions[] = {-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f};
    float colors[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};


    buffer_ = new BufferObject(GL_ARRAY_BUFFER, 24, positions, GL_STATIC_DRAW);
    colors_ = new BufferObject(GL_ARRAY_BUFFER, 36, colors, GL_STATIC_DRAW);
    vertexArray_ = new VertexArray();
    vertexArray_->SetAttribute(buffer_, 0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    vertexArray_->SetAttribute(colors_, 1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

Triangle::~Triangle()
{
    delete program_;
}

void Triangle::Draw() const
{
    program_->Bind();
    vertexArray_->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
  