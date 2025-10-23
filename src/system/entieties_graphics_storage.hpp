#ifndef CONOR_ENTIETIES_GRAPHICS_STORAGE_HPP
#define CONOR_ENTIETIES_GRAPHICS_STORAGE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "../board/tile.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Entieties_graphics_storage
{
public:
    void Set_tiles_tex(std::string tiles_tex_path, int tiles_amount, sf::Vector2i tile_size_ = {16,16});
    void Set_tile_to_sprite(sf::Sprite &sprite, int tile_id, int title_state);
    sf::Vector2i Get_tile_size() {return tile_size;};
private:
    sf::Texture tiles_tex{};
    sf::Vector2i tile_size{};
    std::vector< std::vector<sf::IntRect> > tiles_tex_possitions;
    std::vector<Entities> tiles_order{Entities::player,Entities::goblin,Entities::skieleton};
};

}

#endif // CONOR_ENTIETIES_GRAPHICS_STORAGE_H
