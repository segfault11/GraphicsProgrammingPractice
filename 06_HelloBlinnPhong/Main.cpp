#include "Framework/APP/Application.h"
#include "Framework/APP/GUIElement.h"
#include <iostream>
#include "MeshRenderer.h"
#include "FPSCounter.h"
#include "Framework/OBJ/Object.h"


void errHandler(const std::string& filename, unsigned int lineNo, const std::string& line)
{
    std::cout << line << std::endl;
}


int main(int argc, char const *argv[])
{
    Obj::SetErrorHander(errHandler);
    // const Obj::File* f = Obj::Load("RedCube.obj");
    // Obj::Dump(f);
    // Obj::Release(&f);
    APP::Init("HelloBlinnPhong", 0, 0, 800, 600);
    APP::Camera cam(        
            Math::Vector3F(0.0f, 1.0f, -4.25f), 
            Math::Vector3F(0.0f, 0.0f, 0.0f),
            Math::Vector3F(0.0f, 1.0f, 0.0f),
            60.0f, 4.0f/3.0f, 0.001f, 10.0f
        );
            
    APP::SetCamera(cam);
    MeshRenderer mrenderer("RedCube.obj");
    APP::RegisterDrawable(mrenderer);
    APP::TextureAtlas atlas("Inconsolata.otf", 18);
    FPSCounter element("", Math::Vector2I(700, 575), atlas);
    APP::RegisterGUIElement(element);
    APP::Run();
    APP::Destroy();
    return 0;
}
