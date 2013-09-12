#include "Camera.h"
#include <sstream>
#include <iostream>
//------------------------------------------------------------------------------
SDL::Camera::Camera()
:
    eye_(0.0f, 0.0f, 0.0f),
    u_(1.0f, 0.0f, 0.0f),
    v_(0.0f, 1.0f, 0.0f),
    n_(0.0f, 0.0f, 1.0f)
{
    this->updateViewData();
}
//------------------------------------------------------------------------------
SDL::Camera::~Camera()
{
    
}
//------------------------------------------------------------------------------
SDL::Camera::Camera(            
    const Math::Vector3F& eye, 
    const Math::Vector3F& f,
    const Math::Vector3F& up
)
{
    eye_ = eye;

    n_ = eye - f;
    n_.Normalize();

    u_ = up.Cross(n_);
    u_.Normalize();

    v_ = n_.Cross(u_);

    this->updateViewData();
}
//------------------------------------------------------------------------------
SDL::Camera& SDL::Camera::operator=(const SDL::Camera& orig)
{
    this->eye_ = orig.eye_;
    this->u_ = orig.u_;
    this->v_ = orig.v_;
    this->n_ = orig.n_;

    for (unsigned int i = 0; i < 16; i++)
    {
        this->data_[i] = orig.data_[i];
    }

    return *this;
}
//------------------------------------------------------------------------------
SDL::Camera::Camera(const SDL::Camera& orig)
{
    *this = orig;
}
//------------------------------------------------------------------------------
std::string SDL::Camera::ToString() const
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
void SDL::Camera::Move(const Math::Vector3F& dir)
{
    eye_ += dir;

    this->updateViewData();   
}
//------------------------------------------------------------------------------
void SDL::Camera::MoveU(float dist)
{
    this->Move(u_*dist);
}
//------------------------------------------------------------------------------
void SDL::Camera::MoveV(float dist)
{
    this->Move(v_*dist);
}
//------------------------------------------------------------------------------
void SDL::Camera::MoveN(float dist)
{
    this->Move(n_*dist);
}
//------------------------------------------------------------------------------
void SDL::Camera::MoveUVN(float distU, float distV, float distN)
{
    Math::Vector3F dir = u_*distU + v_*distV + n_*distN;
    this->Move(dir);
}
//------------------------------------------------------------------------------
void SDL::Camera::RotateU(float ang)
{
    v_ = v_*cos(ang) + u_.Cross(v_)*sin(ang) + u_*(u_.Dot(v_)*(1.0f - cos(ang)));
    n_ = n_*cos(ang) + u_.Cross(n_)*sin(ang) + u_*(u_.Dot(n_)*(1.0f - cos(ang)));
    this->updateViewData();
}
//------------------------------------------------------------------------------
void SDL::Camera::RotateV(float ang)
{
    u_ = u_*cos(ang) + v_.Cross(u_)*sin(ang) + v_*(v_.Dot(u_)*(1.0f - cos(ang)));
    n_ = n_*cos(ang) + v_.Cross(n_)*sin(ang) + v_*(v_.Dot(n_)*(1.0f - cos(ang)));
    this->updateViewData();
}
//------------------------------------------------------------------------------
void SDL::Camera::updateViewData()
{
    data_[0] = u_[0];
    data_[4] = u_[1];
    data_[8] = u_[2];
    data_[12] = -u_.Dot(eye_);

    data_[1] = v_[0];
    data_[5] = v_[1];
    data_[9] = v_[2];
    data_[13] = -v_.Dot(eye_);   

    data_[2] = n_[0];
    data_[6] = n_[1];
    data_[10] = n_[2];
    data_[14] = -n_.Dot(eye_);   

    data_[3] = 0.0f;
    data_[7] = 0.0f;
    data_[11] = 0.0f;
    data_[15] = 1.0f;
}
//------------------------------------------------------------------------------
void SDL::Camera::Notify()
{
    std::list<ICameraObserver*>::iterator start = observers_.begin();
    std::list<ICameraObserver*>::iterator end = observers_.end();

    for (; start != end; start++)
    {
        (*start)->OnCameraUpdate();
    }

}
//------------------------------------------------------------------------------
void SDL::Camera::Register(ICameraObserver& observer)
{
    observers_.push_back(&observer);
}
//------------------------------------------------------------------------------