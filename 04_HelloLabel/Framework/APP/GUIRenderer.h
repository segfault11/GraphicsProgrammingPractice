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

namespace APP 
{
    class GUIRenderer : public IRenderer
    {
    public:
        GUIRenderer(const TextureAtlas& atlas);
        ~GUIRenderer();

        void RegisterGUIElement(const GUIElement& ele);

        virtual void Render();

    private:
        DECL_DEFAULTS(GUIRenderer)

        const TextureAtlas* atlas_;
        const GUIElement* element_;
        GL::Program program_;
        GL::VertexArray* vertexArray_;
        GL::BufferObject* posBuffer_;
        GL::BufferObject* texBuffer_;  
    };
    
}
 
#endif /* end of include guard: GUIRENDERER_H__ */