/*!
** Description of an UI Label
**    
** @since 2013-09-15 
*/
#ifndef LABEL_H__
#define LABEL_H__

#include <string> 
#include "../Math/Vector2.h"

namespace UI
{
    class Label
    {
    public:
        Label(const std::string& text, const Math::Vector2UI& position);
        ~Label();

        const std::string& GetText() const {return text_;}
        const Math::Vector2UI& GetPosition() const {return position_;}
        unsigned int GetLength() const {return text_.size();}

    private:
        std::string text_;
        Math::Vector2UI position_;
    };    
}

 
#endif /* end of include guard: LABEL_H__ */