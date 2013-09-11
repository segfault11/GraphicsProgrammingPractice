#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &vertexArray_);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &vertexArray_);
}

void VertexArray::Bind()
{
    glBindVertexArray(vertexArray_);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::SetAttribute(BufferObject* object, GLuint index, GLint size, 
    GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
{
    this->Bind();
    object->Bind();
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
    object->Unbind();
    this->Unbind();
}