/*!
** Description of OpenGL perspective
**    
** @since 2013-09-11 
*/
#ifndef PERSPECTIVE_H__
#define PERSPECTIVE_H__

#include "glcorearb.h" 
#include <string>

namespace GL
{
    class Perspective
    {
    public:
        Perspective(float l, float r, float b, float t, float n, float f);
        Perspective(float fovy, float aspect, float n, float f);
        ~Perspective() {};

        std::string ToString() const;
 
        const GLfloat* GetData() const {return data_;}
    
    private:
        void setData(float l, float r, float b, float t, float n, float f);

        GLfloat data_[16];
    };
}
 
#endif /* end of include guard: PERSPECTIVE_H__ */