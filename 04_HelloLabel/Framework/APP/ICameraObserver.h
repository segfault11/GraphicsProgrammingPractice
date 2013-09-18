#ifndef ICAMERAOBSERVER_H__
#define ICAMERAOBSERVER_H__

namespace APP
{     
    class Camera;

    class ICameraObserver
    {
    public:
        ICameraObserver(Camera& camera);
        ~ICameraObserver() {};

        virtual void OnCameraUpdate();

    protected:
        APP::Camera* camera_;
    };

}
#endif /* end of include guard: ICAMERAOBSERVER_H__ */