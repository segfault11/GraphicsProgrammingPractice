/*!
** Implementation of an GLSL Object
**  
** @since 2013-08-16
*/
#ifndef PROGRAM_H__
#define PROGRAM_H__

#include <GL/GLEW.h> 
#include "Shader.h"

class Program
{
public:
    Program();
    ~Program();

    void AttachShader(const char* filename, GLenum type);
    void BindAttribLocation(GLuint index, const char* name);
    void BindFragDataLocation(GLuint colorNumber, const char* name);
    void Compile();
    void Bind();
    void Unbind();

private:
    bool compiled_;
    GLuint program_;
    Shader* vertexShader_;
    Shader* fragmentShader_;
};
 
#endif /* end of include guard: PROGRAM_H__ */