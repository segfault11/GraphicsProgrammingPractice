#include "Application.h"
#include <stdexcept>
#include <GL/GLEW.h>
#include <iostream>

static bool initialized_ = false;
static SDL_Window* window_ = NULL;
static SDL_GLContext context_ = NULL;
static float elapsed_ = 0.0f;
static std::list<APP::IEventHandler*> eventHandlers_;
static std::list<APP::IRenderer*> renderer_;
static std::list<APP::IRenderer*> guiRenderer_;
static std::list<APP::IObject*> objects_;

static unsigned int screenWidth_;
static unsigned int screenHeight_;

//------------------------------------------------------------------------------
void APP::Init(
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

    screenWidth_ = width;
    screenHeight_ = height;

    initialized_ = true;
}
//------------------------------------------------------------------------------
void APP::Destroy()
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
void APP::Run() 
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

        //  draw gui renderer
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
            std::list<IRenderer*>::iterator start = renderer_.begin();
            std::list<IRenderer*>::iterator end = renderer_.end();

            for (; start != end; start++)
            {
                (*start)->Render();
            }

        }

        
        //  draw gui renderer
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        {        
            std::list<IRenderer*>::iterator start = guiRenderer_.begin();
            std::list<IRenderer*>::iterator end = guiRenderer_.end();

            for (; start != end; start++)
            {
                (*start)->Render();
            }

        }
        glDisable(GL_BLEND);

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
void APP::RegisterRenderer(IRenderer& renderer)
{
    renderer_.push_back(&renderer);
    objects_.push_back(&renderer);
}
//------------------------------------------------------------------------------
void APP::RegisterGUIRenderer(IRenderer& renderer)
{
    guiRenderer_.push_back(&renderer);
    objects_.push_back(&renderer);
}
//------------------------------------------------------------------------------
void APP::RegisterEventHandler(IEventHandler& eventHandler)
{
    eventHandlers_.push_back(&eventHandler);
    objects_.push_back(&eventHandler);
}
//------------------------------------------------------------------------------
bool APP::IsInitialized()
{
    return initialized_;
}
//------------------------------------------------------------------------------
float APP::GetDeltaTime() 
{
    return elapsed_;
}
//------------------------------------------------------------------------------
unsigned int APP::GetScreenWidth()
{
    return screenWidth_;
}
//------------------------------------------------------------------------------
unsigned int APP::GetScreenHeight()
{
    return screenHeight_;
}
//------------------------------------------------------------------------------
