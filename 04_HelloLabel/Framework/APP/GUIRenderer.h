/*!
** Description of a Renderer for GUI Elements
**    
** @since 2013-09-17
*/
#ifndef GUIRENDERER_H__
#define GUIRENDERER_H__

#include "../GL/Program.h"
#include "../GL/VertexArray.h"
#include "../GL/BufferObject.h"
#include "TextureAtlas.h" 
#include "IRenderer.h"
#include "GUIElement.h"
#include <list>

namespace APP 
{
    class GUIRenderer : public IRenderer
    {
        /*
        ** Saves references to a gui element and its array and vertex buffer.
        */
        class GUIElementInfo
        {
        public:
            GL::VertexArray* VertexArray;
            GL::BufferObject* BufferObject;
            const APP::GUIElement* GUIElement;
        };

    public:
        GUIRenderer(const TextureAtlas& atlas);
        ~GUIRenderer();

        void RegisterGUIElement(const GUIElement& ele);

        virtual void Render();

    private:
        DECL_DEFAULTS(GUIRenderer)

        std::list<GUIElementInfo> guiElements_;

        const TextureAtlas* atlas_;
        const GUIElement* element_;
        GL::Program program_;
    };
    
}
 
#endif /* end of include guard: GUIRENDERER_H__ */