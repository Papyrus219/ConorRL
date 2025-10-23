#include "./graphics_manager.hpp"
#include <algorithm>

using namespace conor;

void conor::Graphics_manager::Init_window(sf::Vector2u size)
{
    window.create(sf::VideoMode{{size.x , size.y}}, "ConorRL");
    render_area_start = {0,0};
    render_area_end = {static_cast<int> (size.x/100)+1 , static_cast<int>(size.y/100)+1 };

    Set_view();
}

void conor::Graphics_manager::Generate_map()
{
    map_generator.Generate();
    map.player_possition = static_cast<sf::Vector2f>( *Board_generator::start_player_possition );
    Update();
}

void conor::Graphics_manager::Set_view()
{
    sf::View view{};

    sf::Vector2f title_size = static_cast<sf::Vector2f>( tile_storage.Get_tile_size() );
    sf::Vector2i visible_tiles = { render_area_end - render_area_start };

    view.setSize( {title_size.x * visible_tiles.x, title_size.y * visible_tiles.y} );
    view.setCenter( {(title_size.x * visible_tiles.x) / 2.f, (title_size.y * visible_tiles.y) / 2.f } );

    window.setView(view);
    Update();
}

void conor::Graphics_manager::Resize()
{
    sf::Vector2u size = window.getSize();

    render_area_end = {static_cast<int> (size.x/100)+1 , static_cast<int>(size.y/100)+1 };
    Set_view();
}

void conor::Graphics_manager::Render()
{
    sf::Vector2f tile_size = static_cast<sf::Vector2f>( tile_storage.Get_tile_size() );

    int limiter_y = std::min( static_cast<int>( map.dungeon_map.size() ) , render_area_end.y );
    int limiter_x = std::min( static_cast<int>( map.dungeon_map[0].size() ), render_area_end.x );

    window.clear();
    for(int y = render_area_start.y; y < limiter_y; y++)
    {
        for(int x = render_area_start.x; x < limiter_x; x++)
        {
            drawer.setPosition( {tile_size.x*x, tile_size.y*y} );
            switch(map.dungeon_map[y][x] )
            {
                case Tile::floor:
                    tile_storage.Set_tile_to_sprite(drawer,0);
                    break;
                case Tile::wall:
                    tile_storage.Set_tile_to_sprite(drawer,1);
                    break;
                case Tile::exit:
                    tile_storage.Set_tile_to_sprite(drawer,2);
                    break;
            }
            window.draw(drawer);

            switch( (map.entities_map)[y][x] )
            {
                case Entities::player:
                    entieties_storage.Set_tile_to_sprite(drawer,0,1);
                    break;
                case Entities::goblin:
                    entieties_storage.Set_tile_to_sprite(drawer,1,2);
                    break;
                case Entities::skieleton:
                    entieties_storage.Set_tile_to_sprite(drawer,2,0);
                    break;
                case Entities::none:
                    break;
            }
            window.draw(drawer);
        }
    }
    window.display();
}

void conor::Graphics_manager::Update()
{
    // sf::View view = window.getView();
    //
    // view.setCenter( {map.player_possition.x, map.player_possition.y} );
    //
    // window.setView( view );
    //

    //TO FIX!
}
