#include<iostream>

#include "./board/board.hpp"
#include "./board/board_generator.hpp"
#include "./system/graphics_manager.hpp"

int main()
{
    conor::Board map{};
    conor::Board_generator generator{100,100,&map.dungeon_map,&map.entities_map};
    generator.Generate();

    conor::Graphics_manager renderer{&map};
    renderer.tile_storage.Set_tiles_tex("../../img/tiles.png",1,2);

    renderer.Init_window({500,500});

    while(renderer.window.isOpen())
    {
        renderer.Render();
        while(const std::optional event = renderer.window.pollEvent() )
        {
            if (event->is<sf::Event::Closed>())
            {
                renderer.window.close();
            }
        }
    }

    return 0;
}
