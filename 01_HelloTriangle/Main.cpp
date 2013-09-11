/*!
** Renders a color triangle.
** 
** @file Main.cpp	
** @since 2013-09-01
*/
#include "Framework/Shader.h"
#include "Framework/Program.h"
#include "Framework/SDLApplication.h"
#include "Triangle.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    SDLApplication::Init("Hello Triangle", 0, 0, 1000, 800);
    Triangle tri;
	SDLApplication::SetDrawable(&tri);
	SDLApplication::Run();
	SDLApplication::Destroy();
	return 0;
}