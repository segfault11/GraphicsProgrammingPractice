#include "FPSCounter.h"
#include <sstream>
//------------------------------------------------------------------------------
FPSCounter::FPSCounter(    
    const std::string& text, 
    const Math::Vector2I& pos,
    const APP::TextureAtlas& atlas
)
: GUIElement(text, pos, atlas), time_(0.0f)
{
        this->SetText("111");
        this->SetText("113");
}
//------------------------------------------------------------------------------
FPSCounter::~FPSCounter()
{

}
//------------------------------------------------------------------------------
void FPSCounter::Update()
{
    time_ += APP::GetDeltaTime();

    if (time_ > 50.0f)
    {
        int itime = static_cast<int>(1000.0f/APP::GetDeltaTime());

        std::stringstream s;
        s << itime << " fps";
        this->SetText(s.str());

        time_ = 0.0f;
    }
}
//------------------------------------------------------------------------------