#ifndef CAMERACONTROLLER_H__
#define CAMERACONTROLLER_H__
 
#include "Framework/SDL/IEventHandler.h"
#include "Framework/SDL/Camera.h"

class CameraController : public SDL::IEventHandler 
{
public:
    CameraController(SDL::Camera& camera);
    ~CameraController() {};

    virtual void OnKeyDown(SDL_Keycode key);
    virtual void OnKeyUp(SDL_Keycode key);
    virtual void Update();

private:
    float speedU_;
    float speedV_;
    float speedN_;

    float angU_;
    float angV_;

    SDL::Camera* camera_;
};
 
#endif /* end of include guard: CAMERACONTROLLER_H__ */