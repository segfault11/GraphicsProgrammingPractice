/*!
** Wrapper of an OpenGL Vertex Array Object.
**  
** @since 2013-08-20
*/
#ifndef VERTEXARRAYOBJECT_H__
#define VERTEXARRAYOBJECT_H__

#ifdef __APPLE__
    #include <GL/GLEW.h> 
#else 
    #include <GL/glew.h>
#endif
#include "BufferObject.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    operator GLuint(){return vertexArray_;};

    void SetAttribute(BufferObject* object, GLuint index, GLint size, 
        GLenum type, GLboolean normalized, GLsizei stride, const void* offset);
    void Bind();
    void Unbind();

private:
    VertexArray(const VertexArray& orig);
    VertexArray& operator=(const VertexArray& orig);


    GLuint vertexArray_;
};
 
#endif /* end of include guard: VERTEXARRAYOBJECT_H__ */