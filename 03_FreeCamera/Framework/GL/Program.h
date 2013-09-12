/*!
** Implementation of an GLSL Object
**  
** @since 2013-08-16
*/
#ifndef PROGRAM_H__
#define PROGRAM_H__

#include <GL/GLEW.h> 
#include "Shader.h"

namespace GL
{
    class Program
    {
    public:
        Program();
        ~Program();

        void AttachShader(const char* filename, GLenum type);
        void BindAttribLocation(GLuint index, const char* name);
        void BindFragDataLocation(GLuint colorNumber, const char* name);

        void SetMat4(const char* name, const GLfloat* data);

        void Compile();
        void Bind() const;
        void Unbind() const;

    private:
        bool compiled_;
        GLuint program_;
        Shader* vertexShader_;
        Shader* fragmentShader_;
    };
}
 
#endif /* end of include guard: PROGRAM_H__ */