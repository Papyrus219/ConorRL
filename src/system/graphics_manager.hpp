#ifndef CONOR_GRAPHICS_MANAGER_HPP
#define CONOR_GRAPHICS_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "../board/board_generator.hpp"
#include "./tile_storage.hpp"
#include "./entieties_graphics_storage.hpp"
#include "../tools/observer.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Graphics_manager: public Observer
{
public:
    void Init_window(sf::Vector2u size);
    void Render();
    void Update();
    void Resize();
    void onNotify(Event event, Being * entity) override;
    void Generate_map(Player* &player, std::vector<Enemy*> &enemies);

    Board map{};
    Tile_storage tile_storage{};
    Entieties_graphics_storage entieties_storage{};
    sf::RenderWindow window{};

    ~Graphics_manager() override = default;
private:
    void Set_view();
    sf::Vector2i render_area_start{};
    sf::Vector2i render_area_end{};

    sf::Texture tmp{};
    sf::Sprite drawer{tmp};
    Board_generator map_generator{100,100,&map};
};

}

#endif // CONOR_GRAPHICS_MANAGER_HPP
