#include "Perspective.h"
#include <cmath>
#include <sstream>
//------------------------------------------------------------------------------
GL::Perspective::Perspective(
    float l, float r, 
    float b, float t, 
    float n, float f
)
{
    this->setData(l, r, b, t, n, f);
}
//------------------------------------------------------------------------------
GL::Perspective::Perspective(float fovy, float aspect, float n, float f)
{
        float t = tanf((fovy/2.0)*(3.141593f/180.0f));
        float h = n*t;
        float w = h*aspect;

        this->setData(-w, w, -h, h, n, f);
}
//------------------------------------------------------------------------------
void GL::Perspective::setData(
    float l, float r, 
    float b, float t, 
    float n, float f
)
{
    data_[0] = 2.0f*n/(r - l);
    data_[1] = 0.0f;
    data_[2] = 0.0f;
    data_[3] = 0.0f;

    data_[4] = 0.0f;
    data_[5] = 2.0f*n/(t - b);
    data_[6] = 0.0f;
    data_[7] = 0.0f;

    data_[8] = (r + l)/(r - l);
    data_[9] = (t + b)/(t - b);
    data_[10] = -(f + n)/(f - n);
    data_[11] = -1.0f;

    data_[12] = 0.0f;
    data_[13] = 0.0f;
    data_[14] = -2.0f*f*n/(f - n);
    data_[15] = 0.0f;     
}
//------------------------------------------------------------------------------
std::string GL::Perspective::ToString() const
{
    std::stringstream s;

    s << "[ ";

    for (unsigned int i = 0; i < 16; i++)
    {
        s << data_[i] << " ";
    }

    s << "]";

    return s.str();
}
//------------------------------------------------------------------------------







