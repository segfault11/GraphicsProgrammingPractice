#ifndef FPSCOUNTER_H__
#define FPSCOUNTER_H__
 
#include "Framework/APP/GUIElement.h"
#include "Framework/APP/Application.h"

class FPSCounter : public APP::GUIElement
{
public:
    FPSCounter(    
        const std::string& text, 
        const Math::Vector2I& pos,
        const APP::TextureAtlas& atlas
    );
    ~FPSCounter();

    virtual void Update();

private:
    float time_; 
};
 
#endif /* end of include guard: FPSCOUNTER_H__ */