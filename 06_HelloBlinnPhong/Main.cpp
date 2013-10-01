#include "Framework/APP/Application.h"
#include "Framework/APP/GUIElement.h"
#include <iostream>
#include "MeshRenderer.h"
#include "FPSCounter.h"
#include "Framework/OBJ/Object.h"


int main(int argc, char const *argv[])
{
    // const Obj::File* f = Obj::Load("bunny.obj", NULL);
    // Obj::Dump(f);
    // Obj::ReleaseFile(&f);
    APP::Init("HelloBlinnPhong", 0, 0, 800, 600);
    APP::Camera cam(        
            Math::Vector3F(0.0f, 0.0f, -0.25f), 
            Math::Vector3F(0.0f, 0.0f, 0.0f),
            Math::Vector3F(0.0f, 1.0f, 0.0f),
            60.0f, 4.0f/3.0f, 0.001f, 1.0f
        );
            
    APP::SetCamera(cam);
    MeshRenderer mrenderer("Bunny.obj");
    APP::RegisterDrawable(mrenderer);
    APP::TextureAtlas atlas("Inconsolata.otf", 18);
    FPSCounter element("", Math::Vector2I(700, 575), atlas);
    APP::RegisterGUIElement(element);
    APP::Run();
    APP::Destroy();
    return 0;
}
