#ifndef CONOR_TILES_HPP
#define CONOR_TILES_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "../board/tile.hpp"

namespace conor
{

class Tile_storage
{
public:
    void Set_tiles_tex(std::string tiles_tex_path, int rows_amount = 2, int columns_amount = 2 , sf::Vector2i tile_size_ = {16,16});
    void Set_tile_to_sprite(sf::Sprite &sprite, int tile_id);
    sf::Vector2i Get_tile_size() {return tile_size;};

private:
    sf::Texture tiles_tex{};
    sf::Vector2i tile_size{};
    std::vector<sf::IntRect> tiles_tex_possitions{};
    std::vector<Tile> tiles_order{Tile::floor,Tile::wall,Tile::exit};
};


}


#endif
