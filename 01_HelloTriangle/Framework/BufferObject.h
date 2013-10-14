/*!
** Wrapper of a OpenGL Buffer Object
**  
** @since 2013-08-20
*/
#ifndef VERTEXBUFFER_H__
#define VERTEXBUFFER_H__
 
#ifdef __APPLE__
    #include <GL/GLEW.h> 
#else 
    #include <GL/glew.h>
#endif

class BufferObject
{
public:
    BufferObject(
        GLenum target, 
        GLsizeiptr size, 
        const void* data, 
        GLenum usage
    );
    ~BufferObject();

    operator GLuint(){return buffer_;};
    void Bind();
    void Unbind();

    void* GetData();

private:
    BufferObject();
    BufferObject(const BufferObject& orig);
    BufferObject& operator=(const BufferObject& orig);

    GLuint buffer_;
    GLenum target_;
    GLsizeiptr size_;
};

#endif /* end of include guard: VERTEXBUFFER_H__ */