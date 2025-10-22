#include "./tile_storage.hpp"
#include <iostream>

using namespace conor;

void conor::Tile_storage::Set_tiles_tex(std::string tiles_tex_path, int rows_amount, int columns_amount, sf::Vector2i tile_size_)
{
    tile_size = tile_size_;

    if(!tiles_tex.loadFromFile(tiles_tex_path))
    {
        std::cerr << "Jestem na Steam decku\n";
    }

    tiles_tex_possitions.clear();

    int tiels_loaded{};
    for(int i=0;i<rows_amount;i++)
    {
        for(int j=0;j<columns_amount;j++)
        {
            tiles_tex_possitions.push_back( sf::IntRect{ {tile_size.x*j,tile_size.y*i},{tile_size.x,tile_size.y} } );
            tiels_loaded++;
            if(tiels_loaded == tiles_order.size()) return;
        }
    }
}

void conor::Tile_storage::Set_tile_to_sprite(sf::Sprite &sprite, int tile_id)
{
    sprite.setTexture(tiles_tex);
    sprite.setTextureRect( tiles_tex_possitions[tile_id] );
}
