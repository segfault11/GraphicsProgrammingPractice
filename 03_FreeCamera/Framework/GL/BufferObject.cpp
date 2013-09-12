#include "BufferObject.h"
#include "../Error/Error.h"

//------------------------------------------------------------------------------
//  BUFFER OBJECT'S DEFINITION
//------------------------------------------------------------------------------

GL::BufferObject::BufferObject()
: buffer_(0)
{
    glGetError();
    glGenBuffers(1, &buffer_);

    GLenum error = glGetError();
    if (GL_NO_ERROR != error)
    {
        ERROR_REPORT((const char*)gluErrorString(error));
    }
}

GL::BufferObject::~BufferObject()
{
    glDeleteBuffers(1, &buffer_);
}

void GL::BufferObject::SetData(    
    GLenum target, 
    GLsizeiptr size, 
    const void* data, 
    GLenum usage
)
{
    glGetError();
    glBindBuffer(target, buffer_);
    glBufferData(target, size, data, usage);
    GLenum error = glGetError();
    if (GL_NO_ERROR != error)
    {
        ERROR_REPORT((const char*)gluErrorString(error));
    }    
}

void GL::BufferObject::Bind()
{
    glBindBuffer(target_, buffer_);
}

void GL::BufferObject::Unbind()
{
    glBindBuffer(target_, 0);
}