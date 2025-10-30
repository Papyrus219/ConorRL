#include "./player/input/input_handler.hpp"
#include "./board/board.hpp"
#include "./board/board_generator.hpp"
#include "./system/graphics/graphics_manager.hpp"
#include "./board/path_finder.hpp"
#include "./enemies/enemies_manager.hpp"
#include "./items/item_manager.hpp"

int main()
{
    std::shared_ptr<conor::Player> player;
    conor::Enemies_manager eny_manager{};
    conor::Item_manager itm_manager{};

    conor::Graphics_manager renderer{};
    renderer.Set_path_to_enemies_stats("../../data/beings");
    renderer.Generate_map(player,eny_manager.Get_enemies_ptr(),itm_manager.Get_items_ptr());
    renderer.tile_storage.Set_tiles_tex("../../img/tiles/tiles.png",1,2,{16,16});
    renderer.entieties_storage.Set_tiles_tex("../../img/entieties/entieties.png",4,{16,16});
    renderer.item_storage.Set_item_tex("../../img/items/items.png",3,{1,2,0});
    renderer.Set_player(player);

    conor::Path_finder path_finder{&renderer.map,eny_manager.Get_enemies_ptr()};

    conor::Input_handler handler{player};
    handler.interacter.emplace(&renderer.map);
    handler.interacter->subject.Add_observer( &renderer );
    handler.interacter->subject.Add_observer( &path_finder );
    handler.interacter->subject.Add_observer( &eny_manager );

    renderer.Init_window({1000,1000});

    auto items = itm_manager.Get_items_ptr();

    for(auto item : *items)
        std::cerr << item.use_count() << '\n';

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
                handler.Handle_input(key);

                for(auto item : *items)
                    std::cerr << item.use_count() << '\n';
            }
        }

        renderer.Render();
    }

    return 0;
}
