/*!
** Wrapper of an opengl shader.
**  
** @since 2013-08-19 
*/
#ifndef SHADER_H__
#define SHADER_H__
 
#include <GL/GLEW.h>
namespace GL
{
    class Shader
    {
    public:
        Shader(const char* filename, GLenum type);
        ~Shader();

        operator GLuint() {return shader_;}; 

    private:
        GLuint shader_;

    };
}
#endif /* end of include guard: SHADER_H__ */