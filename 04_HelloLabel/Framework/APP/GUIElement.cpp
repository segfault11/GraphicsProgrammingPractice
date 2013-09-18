#include "GUIElement.h"
//------------------------------------------------------------------------------
APP::GUIElement::GUIElement(const std::string& text, const Math::Vector2I& pos)
:
    text_(text),
    position_(pos)
{

}
//------------------------------------------------------------------------------
APP::GUIElement::~GUIElement()
{
    
}
//------------------------------------------------------------------------------
