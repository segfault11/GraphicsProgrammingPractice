#include "IEventHandler.h"
#include <iostream>
//------------------------------------------------------------------------------
void SDL::IEventHandler::OnEvent(const SDL_Event& event)
{
    switch(event.type) 
    {
        case SDL_KEYDOWN: 

            if (event.key.repeat == 1)
            {
                return;
            }

            OnKeyDown(event.key.keysym.sym);
            break;
        
        case SDL_KEYUP: 
            OnKeyUp(event.key.keysym.sym);
            break;
    }   
}
//------------------------------------------------------------------------------
void SDL::IEventHandler::OnKeyDown(SDL_Keycode key)
{

}
//------------------------------------------------------------------------------
void SDL::IEventHandler::OnKeyUp(SDL_Keycode key)
{

}
//------------------------------------------------------------------------------