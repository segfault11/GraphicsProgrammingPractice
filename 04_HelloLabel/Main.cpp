#include "Framework/APP/Application.h"
#include "Framework/APP/TextureAtlas.h"
#include "Framework/APP/GUIRenderer.h"
#include "Framework/UI/UserInterface.h"
#include "Framework/UI/Label.h"
#include <iostream>



int main(int argc, char const *argv[])
{
    APP::Init("HelloLabel", 0, 0, 800, 600);
    APP::TextureAtlas atlas("Inconsolata.otf", 72);
    APP::GUIRenderer renderer(atlas);
    APP::GUIElement element1("Hallo, Welt", Math::Vector2I(50, 50));
    APP::GUIElement element2("Hello, WUUURLD!!?!", Math::Vector2I(100, 100));
    APP::GUIElement element3("65daysofstatic", Math::Vector2I(25, 300));
    element2.SetTextColor(Math::Vector3F(0.0f, 0.0f, 1.0f));
    element3.SetTextColor(Math::Vector3F(1.0f, 0.0f, 0.0f));
    renderer.RegisterGUIElement(element1);
    renderer.RegisterGUIElement(element2);
    renderer.RegisterGUIElement(element3);
    APP::RegisterGUIRenderer(renderer);
    APP::Run();
    APP::Destroy();
    return 0;
}

    // FT_Library library;
    
    // // load the library
    // FT_Error err = FT_Init_FreeType(&library);

    // if (err) 
    // {
    //     std::cout << "could not initialize FT library." << std::endl;
    //     return -1;
    // }

    // FT_Face face;

    // // load the consolas font (face)
    // err = FT_New_Face(
    //         library,
    //         "Courier New.ttf",
    //          0,
    //         &face 
    //     );

    // if (err) 
    // {
    //     std::cout << "could not initialize face." << std::endl;
    //     return -1;
    // }

    // FT_Set_Pixel_Sizes(face, 0, 48);    

    // std::cout << face->num_glyphs << std::endl;

    // FT_GlyphSlot g = face->glyph;


    //     if (FT_Load_Char(face, 'A', FT_LOAD_RENDER))
    //     {
    //         std::cout << FT_Load_Char(face, 'A', FT_LOAD_RENDER) << std::endl;
    //     }    
    


    // SOIL_save_image("blatest.bmp", SOIL_SAVE_TYPE_BMP, g->bitmap.width, g->bitmap.rows, 1, g->bitmap.buffer);
