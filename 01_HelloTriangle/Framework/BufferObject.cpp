#include "BufferObject.h"
#include "Error.h"

//------------------------------------------------------------------------------
//  BUFFER OBJECT'S DEFINITION
//------------------------------------------------------------------------------

BufferObject::BufferObject(GLenum target, GLsizeiptr size, const void* data, 
    GLenum usage)
: buffer_(0), target_(target), size_(size)
{
    glGetError();
    glGenBuffers(1, &buffer_);
    glBindBuffer(target, buffer_);
    glBufferData(target, size, data, usage);

    GLenum error = glGetError();
    if (GL_NO_ERROR != error)
    {
        ERROR_REPORT((const char*)gluErrorString(error));
    }
}

BufferObject::~BufferObject()
{
    glDeleteBuffers(1, &buffer_);
}

void BufferObject::Bind()
{
    glBindBuffer(target_, buffer_);
}

void BufferObject::Unbind()
{
    glBindBuffer(target_, 0);
}