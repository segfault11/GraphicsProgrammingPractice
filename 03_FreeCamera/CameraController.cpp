#include "CameraController.h"
#include <iostream>
#include "Framework/SDL/Application.h"
//------------------------------------------------------------------------------
CameraController::CameraController(SDL::Camera& camera)
:
    speedU_(0.0f),
    speedV_(0.0f),
    speedN_(0.0f),
    angU_(0.0f),
    angV_(0.0f),
    camera_(&camera)
{

}
//------------------------------------------------------------------------------
void CameraController::OnKeyDown(SDL_Keycode key)
{
    float speed = 0.00006f;
    
    switch(key)
    {
        case SDLK_r:
            angU_ = 0.0005f;
            break;

        case SDLK_f:
            angU_ = -0.0005f;
            break;

        case SDLK_q:
            angV_ = 0.0005f;
            break;

        case SDLK_e:
            angV_ = -0.0005f;
            break;

        case SDLK_w:
            speedN_ = speed;
            break;

        case SDLK_s:
            speedN_ = -speed;    
            break;

        case SDLK_a:
            speedU_ = -speed;
            break;

        case SDLK_d:
            speedU_ = speed;
            break;
    }
}
//------------------------------------------------------------------------------
void CameraController::OnKeyUp(SDL_Keycode key)
{
    switch(key)
    {
        case SDLK_r:
            angU_ = -0.0f;
            break;

        case SDLK_f:
            angU_ = 0.0f;
            break;

        case SDLK_q:
            angV_ = -0.0f;
            break;

        case SDLK_e:
            angV_ = 0.0f;
            break;

        case SDLK_w:
            speedN_ = 0.0f;
            break;

        case SDLK_s:
            speedN_ = 0.0f;    
            break;

        case SDLK_a:
            speedU_ = 0.0f;
            break;

        case SDLK_d:
            speedU_ = 0.0f;
            break;
    }
    
}
//------------------------------------------------------------------------------
void CameraController::Update()
{
    camera_->RotateU(angU_*SDL::Application::GetDeltaTime());
    camera_->RotateV(angV_*SDL::Application::GetDeltaTime());

    camera_->MoveUVN(
        speedU_*SDL::Application::GetDeltaTime(),
        speedV_*SDL::Application::GetDeltaTime(),
        -speedN_*SDL::Application::GetDeltaTime()
    );

    camera_->Notify();
}
//------------------------------------------------------------------------------