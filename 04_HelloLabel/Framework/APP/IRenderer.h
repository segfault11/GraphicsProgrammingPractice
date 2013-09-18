#ifndef IRENDERER_H__
#define IRENDERER_H__

#include "IObject.h"

namespace APP
{
    class IRenderer : public IObject
    {
    public:
        IRenderer() {};
        ~IRenderer() {};

        virtual void Render();
    };    
}
 
#endif /* end of include guard: IRENDERER_H__ */