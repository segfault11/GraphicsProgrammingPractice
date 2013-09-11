/*!
** Description of an OpenGL camera
**    
** @since 2013-09-10
*/
#ifndef CAMERA_H__
#define CAMERA_H__

#include "glcorearb.h"
#include "../Math/Vector3.h"
#include <string>

namespace GL
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

        Camera(
            const Math::Vector3F& eye, 
            const Math::Vector3F& f,
            const Math::Vector3F& up
        );

        Camera(const Camera& orig);
        Camera& operator=(const Camera& orig);

        std::string ToString() const;

        const GLfloat* GetData() const {return data_;};

    private:
        void updateViewData();

        Math::Vector3F eye_;
        Math::Vector3F u_, v_, n_;

        GLfloat data_[16];
    };
}
 
#endif /* end of include guard: CAMERA_H__ */