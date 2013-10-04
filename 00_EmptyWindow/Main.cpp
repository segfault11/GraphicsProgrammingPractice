/*!
** Creates an empty window using SDL2.
**	
** @file Main.cpp
** @since 13-08-13
*/
#include <iostream>
#include <SDL2/SDL.h>

static SDL_Window* window;

int main(int argc, const char** argv)
{

	// initialize SDL Library
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Could not initialize SDL." << std::endl;
		return 1;
	}

	// create a window
	window = SDL_CreateWindow(
			"Empty Window", 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			600,
			600,
			SDL_WINDOW_SHOWN
		);

	if (window == NULL)
	{
		std::cerr << "Could not create a window." << std::endl;
		SDL_Quit();
		return 1;
	}

	// wait three seconds
	SDL_Delay(3000);

	// clean up
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
