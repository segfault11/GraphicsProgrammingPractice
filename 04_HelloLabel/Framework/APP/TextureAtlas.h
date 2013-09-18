/*!
** Description of a Texture Atlas for rendering fonts
**    
** @since 2013-09-16
*/
#ifndef TEXTUREATLAS_H__
#define TEXTUREATLAS_H__
 
#include <string>
#include "../Util.h"
#include "../GL/Texture2D.h"

namespace APP
{
    class TextureAtlas
    {
    public:
        TextureAtlas(const std::string& font, unsigned int fontSize);
        ~TextureAtlas();

        int GetCharWidth(char c) const {return charWidth_[static_cast<int>(c)];}
        int GetCharOffset(char c) const {return charOffset_[static_cast<int>(c)];}
        int GetHeight() const {return height_;}
        int GetWidth() const {return width_;}

        /*!
        ** Binds the texture atlas to a texture unit.
        */
        void Bind(int i) const;

        void SaveToBMP(const std::string& filename) const;

    public:
        DECL_DEFAULTS(TextureAtlas)

        GL::Tex2DR8FR8UI* atlas_;
        int charWidth_[128];
        int charOffset_[128];
        int width_;
        int height_;
    };
}
 
#endif /* end of include guard: TEXTUREATLAS_H__ */