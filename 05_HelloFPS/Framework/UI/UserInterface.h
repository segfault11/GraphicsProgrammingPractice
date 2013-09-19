/*!
** Description of the GUI
**    
** @since 2013-09-15 
*/
#ifndef USERINTERFACE_H__
#define USERINTERFACE_H__

#include <string>
#include "../Error/Error.h"
#include "../UI/Label.h"
#include "../GL/Texture2D.h"
#include "../GL/VertexArray.h"

namespace UI
{

    /*!
    ** Initializes to GUI sub system
    **    
    ** @param font Filename of the font to be used.
    ** @param fontSize Size of the font to be used. 
    */
    void Init(const std::string& font, unsigned int fontSize); 
    void Destroy();

    void AddLabel(const UI::Label& label);
}

 
#endif /* end of include guard: USERINTERFACE_H__ */
