#include<iostream>
#include <fstream>
#include "./player/input/input_handler.hpp"
#include "./board/board.hpp"
#include "./board/board_generator.hpp"
#include "./system/graphics_manager.hpp"
#include "./board/path_finder.hpp"
#include "./enemies/enemies_manager.hpp"

int main()
{
    std::shared_ptr<conor::Player> player;
    conor::Enemies_manager eny_manager{};

    conor::Being::subject.Add_observer(&eny_manager);

    conor::Graphics_manager renderer{};
    renderer.Set_path_to_enemies_stats("../../data/beings");
    renderer.Generate_map(player,eny_manager.Get_enemies_ptr());
    renderer.tile_storage.Set_tiles_tex("../../img/tiles/tiles.png",1,2,{16,16});
    renderer.entieties_storage.Set_tiles_tex("../../img/entieties/entieties.png",4,{16,16});

    conor::Path_finder path_finder{&renderer.map,eny_manager.Get_enemies_ptr()};

    conor::Input_handler handler{player};
    handler.attacker.emplace(&renderer.map);
    handler.mover.emplace(&renderer.map, &*handler.attacker);
    handler.mover->subject.Add_observer( &renderer );
    handler.mover->subject.Add_observer( &path_finder );

    renderer.Init_window({1000,1000});

    while(renderer.window.isOpen())
    {
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
            else if (auto key_pressed = event->getIf<sf::Event::KeyPressed>())
            {
                sf::Keyboard::Key key = key_pressed->code;
                handler.Handle_input_broad(key);
            }
        }

        renderer.Render();
    }

    return 0;
}
