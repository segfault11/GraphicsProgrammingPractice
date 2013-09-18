#include "GUIElement.h"
//------------------------------------------------------------------------------
APP::GUIElement::GUIElement(const std::string& text, const Math::Vector2I& pos)
:
    text_(text),
    position_(pos),
    textColor_(Math::Vector3F(0.0f, 0.0f, 0.0f))
{

}
//------------------------------------------------------------------------------
APP::GUIElement::~GUIElement()
{
    
}
//------------------------------------------------------------------------------
