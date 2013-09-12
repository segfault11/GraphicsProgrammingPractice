#ifndef ICAMERAOBSERVER_H__
#define ICAMERAOBSERVER_H__

#include "IObject.h"

namespace SDL
{     
    class Camera;

    class ICameraObserver : public IObject
    {
    public:
        ICameraObserver(Camera& camera);
        ~ICameraObserver() {};

        virtual void OnCameraUpdate();

    protected:
        SDL::Camera* camera_;
    };

}
#endif /* end of include guard: ICAMERAOBSERVER_H__ */