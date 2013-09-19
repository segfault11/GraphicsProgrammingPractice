#include "Framework/APP/Application.h"
#include "Framework/APP/TextureAtlas.h"
#include "Framework/APP/GUIElement.h"
#include "Framework/UI/UserInterface.h"
#include "Framework/UI/Label.h"
#include <iostream>
#include "MeshRenderer.h"

int main(int argc, char const *argv[])
{
    APP::Init("HelloFPS", 0, 0, 800, 600);
    APP::Camera cam(        
            Math::Vector3F(0.0f, 0.0f, -0.25f), 
            Math::Vector3F(0.0f, 0.0f, 0.0f),
            Math::Vector3F(0.0f, 1.0f, 0.0f)
        );
    APP::SetCamera(cam);
    MeshRenderer mrenderer("Bunny.obj");
    APP::RegisterDrawable(mrenderer);
    APP::TextureAtlas atlas("Inconsolata.otf", 42);
    APP::GUIElement element("65", Math::Vector2I(700, 550), atlas);
    APP::GUIElement element2("65", Math::Vector2I(200, 550), atlas);
    APP::RegisterGUIElement(element);
    APP::RegisterGUIElement(element2);
    APP::Run();
    APP::Destroy();
    return 0;
}
