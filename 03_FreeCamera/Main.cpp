#include "Framework/SDL/Application.h"
#include "Framework/OBJ/File.h"
#include <iostream>
#include "Framework/Math/Tuple.h"
#include "MeshRenderer.h"
#include "Framework/Math/Matrix4.h"
#include "Framework/GL/Perspective.h"
#include "CameraController.h"

int main(int argc, char const *argv[])
{
    SDL::Application::Init("FreeCamera", 0, 0, 600, 600);
    SDL::Camera cam(        
            Math::Vector3F(0.0f, 0.0f, -0.25f), 
            Math::Vector3F(0.0f, 0.0f, 0.0f),
            Math::Vector3F(0.0f, 1.0f, 0.0f)
        );
    MeshRenderer renderer("Bunny.obj", cam);
    CameraController controller(cam);
    SDL::Application::RegisterRenderer(renderer);    
    SDL::Application::RegisterEventHandler(controller);
    SDL::Application::Run();
    SDL::Application::Destroy();

    return 0;
}