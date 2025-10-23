#include<iostream>

#include "./board/board.hpp"
#include "./board/board_generator.hpp"
#include "./system/graphics_manager.hpp"

int main()
{



    conor::Graphics_manager renderer{};
    renderer.Generate_map();
    renderer.tile_storage.Set_tiles_tex("../../img/tiles/tiles.png",1,2,{16,16});
    renderer.entieties_storage.Set_tiles_tex("../../img/entieties/entieties.png",3,{16,16});

    renderer.Init_window({1000,1000});

    while(renderer.window.isOpen())
    {
        renderer.Render();
        while(const std::optional event = renderer.window.pollEvent() )
        {
            if (event->is<sf::Event::Closed>())
            {
                renderer.window.close();
            }
            else if(event->is<sf::Event::Resized>())
            {
                renderer.Resize();
            }
        }
    }

    return 0;
}
