#include "SDLApplication.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#ifdef __APPLE__
    #include <GL/GLEW.h> 
#else 
    #include <GL/glew.h>
#endif

// INITIALIZE STATIC MEMBER
bool SDLApplication::initialized_ = false;
SDL_Window* SDLApplication::window_ = NULL;
SDL_GLContext SDLApplication::context_ = NULL;
const IDrawable* SDLApplication::drawable_ = NULL;

void SDLApplication::Init(
    const char* name, 
    unsigned int x, 
    unsigned int y, 
    unsigned int width, 
    unsigned int height
)
{
    if (initialized_)
    {
        return;
    }

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error(SDL_GetError());       
    }

    // Set OpenGL context attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 24);

    // create a new window  
    window_ = SDL_CreateWindow(
            "Hello Triangle", 
            0, 0, 
            width, height, 
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN 
        );

    if (window_ == NULL)
    {
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }

    // create an OpenGL context
    context_ = SDL_GL_CreateContext(window_);
    
    if (context_ == NULL)
    {
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }


    // set up GLEW
    glewExperimental = GL_TRUE; 

    if (GLEW_OK != glewInit())
    {
        printf("glewInit failed\n");
    }
    else
    {
        printf("glewInit succeded\n");
    }

    initialized_ = true;
}

void SDLApplication::Destroy()
{
    if (!initialized_)
    {
        return;
    }

    SDL_GL_DeleteContext(context_);
    SDL_DestroyWindow(window_);
    SDL_Quit();

    initialized_ = false;
}

void SDLApplication::Run() 
{
    if (!initialized_)
    {
        throw std::runtime_error("Application not initialized");
    }

    SDL_Event event; 
    bool done = false;

    while (!done) 
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || event.type == SDL_QUIT)
            {
                done = true;
            }    
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (drawable_)
        {
            drawable_->Draw();
        }

        SDL_GL_SwapWindow(window_);
    }
    
}

void SDLApplication::SetDrawable(const IDrawable *drawable)
{
    drawable_ = drawable;
}
