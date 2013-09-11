/*!
** Definition of a default SDL application.
**  
** @file SDLApplication.h
** @since 2013-08-15 
*/
#ifndef SDLAPPLICATION_H__
#define SDLAPPLICATION_H__

#include <SDL2/SDL.h>
#include "IDrawable.h"

class SDLApplication
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

    static void SetDrawable(const IDrawable* drawable);

private:
    SDLApplication();
    ~SDLApplication();

    static bool initialized_;
    static SDL_Window* window_;
    static SDL_GLContext context_;
    static const IDrawable* drawable_;
};
 

#endif /* end of include guard: SDLAPPLICATION_H__ */