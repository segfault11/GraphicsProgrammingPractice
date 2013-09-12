/*!
** Definition of a default SDL application.
**  
** @file SDLApplication.h
** @since 2013-08-15 
*/
#ifndef SDLAPPLICATION_H__
#define SDLAPPLICATION_H__

#include <SDL2/SDL.h>
#include "IEventHandler.h"
#include "IRenderer.h"
#include "../GL/IDrawable.h"
#include <list>

namespace SDL
{
    class Application
    {
    public:
        
        /*!
        ** Initialize the application. Creates a window and an OpenGL 3.2 context.
        ** 
        ** @param name Name of the applications (title of the window).
        ** @param x x position of the window.
        ** @param y y position of the window.
        ** @param width width of the window.
        ** @param height height of the window.
        **
        ** @since 2013-08-15 
        */
        static void Init(
            const char* name, 
            unsigned int x, 
            unsigned int y, 
            unsigned int width, 
            unsigned int height
        );
        
        static void Destroy();

        /*!
        ** Enters the main loop of the application.
        **  
        ** @since 2013-08-15
        */
        static void Run();

        static void RegisterRenderer(IRenderer& renderer);
        static void RegisterEventHandler(IEventHandler& eventHandler);

        static float GetDeltaTime();

    private:
        Application();
        ~Application();



        static bool initialized_;
        static SDL_Window* window_;
        static SDL_GLContext context_;
        static GL::IDrawable* drawable_;
        static std::list<IEventHandler*> eventHandlers_;
        static std::list<IRenderer*> renderer_;
        static std::list<IObject*> objects_;

        static float elapsed_; // elapsed time in ms
    };

}

#endif /* end of include guard: SDLAPPLICATION_H__ */