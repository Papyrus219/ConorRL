#include "game.hpp"

using namespace conor;

void conor::Game::Setup()
{
    auto player = resorcer.Get_player();
    auto item_manager = resorcer.Get_item_manager();
    auto enemy_manager = resorcer.Get_enemy_manager();

    conor::Graphics_manager renderer{};
    renderer.Set_path_to_enemies_stats("../../data/beings");
    renderer.Generate_map(player,enemy_manager->Get_enemies_ptr(),item_manager->Get_items_ptr());
    renderer.tile_storage.Set_tiles_tex("../../img/tiles/tiles.png",1,2,{16,16});
    renderer.entieties_storage.Set_tiles_tex("../../img/entieties/entieties.png",4,{16,16});
    renderer.item_storage.Set_item_tex("../../img/items/items.png",3,{1,2,1});
    renderer.Set_player(player);

    looper.path_finder.emplace( &renderer.map,enemy_manager->Get_enemies_ptr() );

    conor::Input_handler handler{player};
    handler.interacter.emplace(&renderer.map);
    handler.interacter->subject.Add_observer( &renderer );
    handler.interacter->subject.Add_observer( &path_finder );
    handler.interacter->subject.Add_observer( &enemy_manager );

}
