#include "Framework/SDLApplication.h"
#include "Framework/OBJ/File.h"
#include <iostream>
#include "Framework/Math/Tuple.h"
#include "MeshRenderer.h"
#include "Framework/Math/Matrix4.h"
#include "Framework/GL/Camera.h"
#include "Framework/GL/Perspective.h"

int main(int argc, char const *argv[])
{
    // GL::Camera cam(        
    //         Math::Vector3F(0.0f, 0.0f, -1.0f), 
    //         Math::Vector3F(0.0f, 0.0f, 0.0f),
    //         Math::Vector3F(0.0f, 1.0f, 0.0f)
    //     );

    // std::cout << cam.ToString() << std::endl;

    // GL::Perspective perspective(60.0f, 1.0f, 0.01f, 10.0f);

    // std::cout << perspective.ToString() << std::endl;


    SDLApplication::Init("HelloMesh", 0, 0, 600, 600);
    MeshRenderer renderer("Bunny.obj");
    SDLApplication::SetDrawable(&renderer);
    SDLApplication::Run();
    SDLApplication::Destroy();

    return 0;
}