#include "game.hpp"

using namespace conor;

void conor::Game::Setup()
{
    looper = std::make_shared<Logic_manager>();
    renderer = std::make_shared<Graphics_manager>();
    resorcer = std::make_shared<Resorces_manager>();
    audier = std::make_shared<Audio_manager>("../../audio/",2);

    looper->renderer = renderer;
    looper->resorcer = resorcer;
    renderer->looper = looper;
    renderer->resorcer = resorcer;
    resorcer->renderer = renderer;
    resorcer->looper = looper;

    renderer->Set_path_to_enemies_stats("../../data/beings");
    renderer->map_generator.Set_resourcer(resorcer);
    renderer->Generate_map();
    renderer->tile_storage.Set_tiles_tex("../../img/tiles/tiles.png",1,3,{16,16});
    renderer->entieties_storage.Set_tiles_tex("../../img/entieties/entieties.png",4,{16,16});
    renderer->item_storage.Set_item_tex("../../img/items/items.png",3,{1,2,1});
    renderer->main_menu_tex.loadFromFile("../../img/menu.png");

    looper->path_finder.emplace( &renderer->map,resorcer->Get_enemy_manager()->Get_enemies_ptr() );
    looper->input_handler.emplace( resorcer->Get_player() );

    looper->input_handler->interacter.emplace(&renderer->map);
    looper->path_finder->subject.Add_observer( &(*audier) );
    looper->input_handler->interacter->subject.Add_observer( &(*audier) );
    looper->input_handler->interacter->subject.Add_observer( renderer.get() );
    looper->input_handler->interacter->subject.Add_observer( &(*looper->path_finder) );
    looper->input_handler->interacter->subject.Add_observer( resorcer->Get_enemy_manager().get() );
    looper->input_handler->interacter->subject.Add_observer( &(*looper) );
}

void conor::Game::Start()
{
    Setup();

    renderer->Init_window({1000,1000});
    looper->Loop();
}
