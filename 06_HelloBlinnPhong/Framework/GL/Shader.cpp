#include "Shader.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include "../Error/Error.h"
#include <sstream>

//------------------------------------------------------------------------------
//  HELPER FORW. DECL.
//------------------------------------------------------------------------------

static const char* readFile(const char* filename);

//------------------------------------------------------------------------------
//  SHADERS DEFINITION
//------------------------------------------------------------------------------
GL::Shader::Shader()
: shader_(0)
{

}
//------------------------------------------------------------------------------
GL::Shader::Shader(const char* source, GLenum type)
: shader_(0)
{
    shader_ = glCreateShader(type);

    if (shader_ == 0)
    {
        ERROR_REPORT("Could not create shader.");
    }

    glShaderSource(shader_, 1, &source, NULL);
    glCompileShader(shader_);

    // check if shader compiled correctly
    GLint status;
    glGetShaderiv(shader_, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader_, infoLogLength, NULL, infoLog);
        
        std::stringstream message;
        message << "Could not compile shader. "  << std::endl;
        message << infoLog << std::endl;

        delete[] infoLog;        
        
        ERROR_REPORT(message.str().c_str());
    }
}
//------------------------------------------------------------------------------
void GL::Shader::Load(const char* filename, GLenum type)
{
    if (shader_ != 0)
    {
        ERROR_WARNING("Shader was already initialized.")
        return;
    }

    const char* source = readFile(filename);

    if (source == NULL)
    {
        ERROR_REPORT("Could not read shader file.");
    }

    shader_ = glCreateShader(type);

    if (shader_ == 0)
    {
        ERROR_REPORT("Could not create shader.");
    }

    glShaderSource(shader_, 1, &source, NULL);
    glCompileShader(shader_);

    // check if shader compiled correctly
    GLint status;
    glGetShaderiv(shader_, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader_, infoLogLength, NULL, infoLog);
        
        std::stringstream message;
        message << "Could not compile shader for: " << filename << std::endl;
        message << infoLog << std::endl;

        delete[] infoLog;        
        
        ERROR_REPORT(message.str().c_str());
    }

    delete[] source;
}

GL::Shader::~Shader()
{
    glDeleteShader(shader_);
}

//------------------------------------------------------------------------------
//  HELPER DEF.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

unsigned long getFileLength(std::ifstream& file)
{
    if (!file.good())
    {
        return 0;
    }

    file.seekg(0, std::ios::end);
    unsigned long length = file.tellg();
    file.seekg(std::ios::beg);
    
    return length;
}
//------------------------------------------------------------------------------
const char* readFile(const char* filename)
{
    std::ifstream file;
    file.open(filename, std::ios::in);

    if (!file)
    {
        return NULL;
    }

    // get length of file
    unsigned long length = getFileLength(file);
    char* buffer = new char[length + 1];

    if (buffer == NULL)
    {
        return NULL;
    }

    buffer[length] = '\0';

    // fill buffer
    unsigned int i = 0;

    while (file.good())
    {
        buffer[i] = file.get();

        if (!file.eof())
        {
            i++;
        }
    }

    buffer[i] = '\0';
    file.close();
    return buffer;
}
//------------------------------------------------------------------------------
