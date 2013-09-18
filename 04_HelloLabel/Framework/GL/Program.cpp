#include "Program.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include "../Error/Error.h"

//------------------------------------------------------------------------------
//                            PUBLIC DEFININTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
GL::Program::Program()
: compiled_(false), program_(0), vertexShader_(NULL), fragmentShader_(NULL)
{
     program_ = glCreateProgram();

     if (program_ == 0)
     {
        throw std::runtime_error("Could not create program.");
     }
}
//------------------------------------------------------------------------------
GL::Program::~Program()
{
    if (!program_)
    {
        return;
    }

    glDeleteProgram(program_);
    delete vertexShader_;
    delete fragmentShader_;
}
//------------------------------------------------------------------------------
void GL::Program::AttachShader(const char* filename, GLenum type)
{
    if (compiled_)
    {
        ERROR_WARNING("Program is already compiled.");
        return;
    }

    Shader* shader = new Shader();
    shader->Load(filename, type);

    // check if a shader was already attached
    switch (type)
    {
        case GL_VERTEX_SHADER:
            
            if (vertexShader_)
            {
                glDetachShader(program_, *vertexShader_);
                delete vertexShader_;
                ERROR_WARNING("Vertex shader was replaced.")
            }

            vertexShader_ = shader;
        
            break;

        case GL_FRAGMENT_SHADER:

            if (fragmentShader_)
            {
                glDetachShader(program_, *fragmentShader_);
                delete fragmentShader_;
                ERROR_WARNING("Vertex shader was replaced.")
            }

            fragmentShader_ = shader;
        
            break;
    }

    glAttachShader(program_, *shader);
}
//------------------------------------------------------------------------------
void GL::Program::AttachShaderFromSource(const char* source, GLenum type)
{
    if (compiled_)
    {
        ERROR_WARNING("Program is already compiled.");
        return;
    }

    Shader* shader = new Shader(source, type);

    // check if a shader was already attached
    switch (type)
    {
        case GL_VERTEX_SHADER:
            
            if (vertexShader_)
            {
                glDetachShader(program_, *vertexShader_);
                delete vertexShader_;
                ERROR_WARNING("Vertex shader was replaced.")
            }

            vertexShader_ = shader;
        
            break;

        case GL_FRAGMENT_SHADER:

            if (fragmentShader_)
            {
                glDetachShader(program_, *fragmentShader_);
                delete fragmentShader_;
                ERROR_WARNING("Vertex shader was replaced.")
            }

            fragmentShader_ = shader;
        
            break;
    }

    glAttachShader(program_, *shader);
}
//------------------------------------------------------------------------------
void GL::Program::BindAttribLocation(GLuint index, const char* name)
{
    if (compiled_)
    {
        ERROR_WARNING("Program was already compiled.")
        return;
    }

    glBindAttribLocation(program_, index, name);
}
//------------------------------------------------------------------------------
void GL::Program::BindFragDataLocation(GLuint colorNumber, const char* name)
{
    if (compiled_)
    {
        ERROR_WARNING("Program was already compiled.")
        return;
    }

    glBindFragDataLocation(program_, colorNumber, name);
}
//------------------------------------------------------------------------------
void GL::Program::Compile()
{
    if (compiled_)
    {
        ERROR_WARNING("Program is already compiled.");
        return;
    }

    if (vertexShader_ == NULL || fragmentShader_ == NULL)
    {
        ERROR_REPORT("Could not compile program.");
    }

    glLinkProgram(program_);

    int status;
    glGetProgramiv(program_, GL_LINK_STATUS, &status);

    if (status != GL_TRUE)
    {
        char* log;
        GLint logLength;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &logLength);
        log = new char[logLength + 1];
        glGetProgramInfoLog(program_, logLength, NULL, log);
        ERROR_REPORT(log);
        delete[] log;
    }

    glDetachShader(program_, *vertexShader_);
    glDetachShader(program_, *fragmentShader_);
    
    compiled_ = true;
}
//------------------------------------------------------------------------------
void GL::Program::Bind() const
{
    ERROR_ASSERT(compiled_)

    glUseProgram(program_);
}
//------------------------------------------------------------------------------
void GL::Program::Unbind() const
{
    ERROR_ASSERT(compiled_)

    glUseProgram(0);
}
//------------------------------------------------------------------------------
void GL::Program::SetMat4(const char* name, const GLfloat* data)
{
    ERROR_ASSERT(compiled_)
    
    this->Bind();
    GLint loc = glGetUniformLocation(program_, name);

    ERROR_ASSERT(loc != -1)

    glUniformMatrix4fv(loc, 1, GL_FALSE, data);
}
//------------------------------------------------------------------------------
void GL::Program::SetInt(const char* name, GLint i)
{
    ERROR_ASSERT(compiled_)
    
    this->Bind();
    GLint loc = glGetUniformLocation(program_, name);

    ERROR_ASSERT(loc != -1)

    glUniform1i(loc, i);
}
//------------------------------------------------------------------------------
void GL::Program::SetIVec2(const char* name, const GLint* ivec)
{
    ERROR_ASSERT(compiled_)
    
    this->Bind();
    GLint loc = glGetUniformLocation(program_, name);

    ERROR_ASSERT(loc != -1)

    glUniform2i(loc, ivec[0], ivec[1]);    
}
//------------------------------------------------------------------------------
