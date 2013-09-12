#ifndef IRENDERER_H__
#define IRENDERER_H__

#include "ICameraObserver.h"

namespace SDL
{
    class IRenderer: public ICameraObserver 
    {
    public:
        IRenderer(Camera& camera): ICameraObserver(camera) {};
        ~IRenderer() {};

        virtual void Render();
    };    
}
 
#endif /* end of include guard: IRENDERER_H__ */