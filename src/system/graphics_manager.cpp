#include "./graphics_manager.hpp"
#include <algorithm>

using namespace conor;

conor::Graphics_manager::Graphics_manager(Board* board): assigned_dung{&board->dungeon_map}, assigned_ent{&board->entities_map}
{

}

void conor::Graphics_manager::Init_window(sf::Vector2u size)
{
    size.x += static_cast<unsigned int> (16 - (size.x % 16) );
    size.y += static_cast<unsigned int> (16 - (size.y % 16) );
    window.create(sf::VideoMode{{size.x , size.y}}, "ConorRL");
    render_area_start = {0,0};
    render_area_end = {static_cast<int>(size.x/16), static_cast<int>(size.y/16) };
}

void conor::Graphics_manager::Render()
{
    sf::Vector2f tile_size = static_cast<sf::Vector2f>( tile_storage.Get_tile_size() );

    window.clear();
    for(int y = render_area_start.y; y < render_area_end.y; y++)
    {
        for(int x = render_area_start.x; x < render_area_end.x; x++)
        {
            drawer.setPosition( {tile_size.x*x, tile_size.y*y} );
            switch( (*assigned_dung)[y][x] )
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
        }
    }
    window.display();
}
