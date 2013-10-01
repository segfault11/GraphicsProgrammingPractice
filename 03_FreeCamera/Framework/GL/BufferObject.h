/*!
** Wrapper of a OpenGL Buffer Object
**  
** @since 2013-08-20
*/
#ifndef VERTEXBUFFER_H__
#define VERTEXBUFFER_H__
 
#include <GL/GLEW.h>

namespace GL
{
    class BufferObject
    {
    public:
        BufferObject();
        ~BufferObject();

        operator GLuint() {return buffer_;}
        
        void SetData(    
            GLenum target, 
            GLsizeiptr size, 
            const void* data, 
            GLenum usage
        );
        void Bind();
        void Unbind();

        void* GetData();

    private:
        BufferObject(const BufferObject& orig);
        BufferObject& operator=(const BufferObject& orig);

        GLuint buffer_;
        GLenum target_;
        GLsizeiptr size_;
    };
}
#endif /* end of include guard: VERTEXBUFFER_H__ */
