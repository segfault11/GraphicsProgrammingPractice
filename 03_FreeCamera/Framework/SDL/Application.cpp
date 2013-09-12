#include "Application.h"
#include <stdexcept>
#include <GL/GLEW.h>
#include <iostream>

// INITIALIZE STATIC MEMBER
bool SDL::Application::initialized_ = false;
SDL_Window* SDL::Application::window_ = NULL;
SDL_GLContext SDL::Application::context_ = NULL;
GL::IDrawable* SDL::Application::drawable_ = NULL;
float SDL::Application::elapsed_ = 0.0f;
std::list<SDL::IEventHandler*> SDL::Application::eventHandlers_;
std::list<SDL::IRenderer*> SDL::Application::renderer_;
std::list<SDL::IObject*> SDL::Application::objects_;

//------------------------------------------------------------------------------
void SDL::Application::Init(
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
            name,
            0, 0, 
            width, height, 
            SDL_WINDOW_SHOWN
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
//------------------------------------------------------------------------------
void SDL::Application::Destroy()
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
//------------------------------------------------------------------------------
void SDL::Application::Run() 
{
    if (!initialized_)
    {
        throw std::runtime_error("Application not initialized");
    }

    SDL_Event event; 
    bool done = false;

    Uint32 currTime = SDL_GetTicks();

    while (!done) 
    {
        // compute the time
        elapsed_ = static_cast<float>(SDL_GetTicks() - currTime);
        currTime = SDL_GetTicks();
 
        // handle events
        while (SDL_PollEvent(&event))
        {
            // Notify all event listeners
            std::list<IEventHandler*>::iterator start = eventHandlers_.begin();
            std::list<IEventHandler*>::iterator end = eventHandlers_.end();

            for (; start != end; start++)
            {
                (*start)->OnEvent(event);
            }


            if (event.type == SDL_QUIT || event.type == SDL_QUIT)
            {
                done = true;
            }    
        }

        
        //  draw
        {
        
            std::list<IRenderer*>::iterator start = renderer_.begin();
            std::list<IRenderer*>::iterator end = renderer_.end();

            for (; start != end; start++)
            {
                (*start)->Render();
            }

        }
        // update all objects
        {
        
            std::list<IObject*>::iterator start = objects_.begin();
            std::list<IObject*>::iterator end = objects_.end();

            for (; start != end; start++)
            {
                (*start)->Update();
            }

        }

        SDL_GL_SwapWindow(window_);

        // SDL_Delay(1000.0f/60.0f);
    }
    
}
//------------------------------------------------------------------------------
void SDL::Application::RegisterRenderer(SDL::IRenderer& renderer)
{
    renderer_.push_back(&renderer);
    objects_.push_back(&renderer);
}
//------------------------------------------------------------------------------
void SDL::Application::RegisterEventHandler(IEventHandler& eventHandler)
{
    eventHandlers_.push_back(&eventHandler);
    objects_.push_back(&eventHandler);
}
//------------------------------------------------------------------------------
float SDL::Application::GetDeltaTime() 
{
    return elapsed_;
}
//------------------------------------------------------------------------------