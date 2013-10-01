/*!
** Wrapper of a OpenGL Buffer Object
**  
** @since 2013-08-20
*/
#ifndef VERTEXBUFFER_H__
#define VERTEXBUFFER_H__
 
#include <GL/glew.h>
//#include "glcorearb.h"

namespace GL
{
    class BufferObject
    {
    public:
        BufferObject(GLenum target, GLsizeiptr size, GLenum usage);
        ~BufferObject();

        operator GLuint() {return buffer_;}
        
        void SetData(GLsizeiptr size, const void* data);

        void Bind();
        void Unbind();

        void* GetData();

    private:
        BufferObject();
        BufferObject(const BufferObject& orig);
        BufferObject& operator=(const BufferObject& orig);

        GLuint buffer_;
        GLenum target_;
        GLenum usage_;
        GLsizeiptr size_;
    };
}
#endif /* end of include guard: VERTEXBUFFER_H__ */
