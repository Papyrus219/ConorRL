#include "entieties_graphics_storage.hpp"
#include <iostream>

using namespace conor;

void conor::Entieties_graphics_storage::Set_tiles_tex(std::string tiles_tex_path, int tile_amount, sf::Vector2i tile_size_)
{
    tile_size = tile_size_;

    if(tiles_tex.loadFromFile(tiles_tex_path))
    {
        tiles_tex_possitions.clear();

        for(int i=0;i<tile_amount;i++)
        {
            tiles_tex_possitions.push_back( std::vector<sf::IntRect>{} );
            for(int j=0;j<4;j++)
            {
                tiles_tex_possitions[i].push_back( sf::IntRect{ {tile_size.x*i,tile_size.y*j}, {tile_size.x,tile_size.y} } );
            }
        }
    }
    else
    {
        std::cerr << "Jestem na Steam decku\n";
    }
}

void conor::Entieties_graphics_storage::Set_tile_to_sprite(sf::Sprite& sprite, int tile_id, int title_state)
{
    sprite.setTexture(tiles_tex);
    sprite.setTextureRect( tiles_tex_possitions[tile_id][title_state] );
}
