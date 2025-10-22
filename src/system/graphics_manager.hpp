#ifndef CONOR_GRAPHICS_MANAGER_HPP
#define CONOR_GRAPHICS_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "../board/board.hpp"
#include "./tile_storage.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Graphics_manager
{
public:
    Graphics_manager(Board *board);
    void Init_window(sf::Vector2u size);
    void Render();

    Tile_storage tile_storage{};
    sf::RenderWindow window{};
private:
    sf::Vector2i render_area_start{};
    sf::Vector2i render_area_end{};

    sf::Texture tmp{};
    sf::Sprite drawer{tmp};
    std::vector< std::vector<Tile> > *assigned_dung;
    std::vector< std::vector<Entities> > *assigned_ent;
};

}

#endif // CONOR_GRAPHICS_MANAGER_HPP
