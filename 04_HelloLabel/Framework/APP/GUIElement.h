/*!
** Description of a GUI element
**    
** @since 2013-09-17
*/
#ifndef GUIELEMENT_H__
#define GUIELEMENT_H__

#include <string> 
#include "../Util.h"
#include "../Math/Vector2.h"

namespace APP
{
    class GUIElement
    {
    public:
        /*
        ** Constructs a GUI element. 
        ** 
        ** @param text Text to be displayed.
        ** @param pos Position on the screen in pixels.
        */
        GUIElement(const std::string& text, const Math::Vector2I& pos);
        ~GUIElement();

        const Math::Vector2I& GetPosition() const {return position_;}
        const std::string& GetText() const {return text_;}

    private:
        DECL_DEFAULTS(GUIElement)

        std::string text_;
        Math::Vector2I position_;
    };
}
 
#endif /* end of include guard: GUIELEMENT_H__ */