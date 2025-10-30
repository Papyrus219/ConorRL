#ifndef CONOR_GRAPHICS_MANAGER_HPP
#define CONOR_GRAPHICS_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "../../board/board_generator.hpp"
#include "./tile_graphics_storage.hpp"
#include "./entieties_graphics_storage.hpp"
#include "./items_graphics_storage.hpp"
#include "../../tools/observer.hpp"

namespace conor {

class Player;

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
    void onNotify(Event event, std::shared_ptr<Being> &entity) override;
    void Generate_map(std::shared_ptr<Player> &player, std::vector< std::shared_ptr<Enemy> > *enemies, std::vector< std::shared_ptr<Item> > *items);
    void Set_path_to_enemies_stats(std::string path_to_enemies);
    void Set_player(std::shared_ptr<Player> &players);

    Board map{};
    Tile_storage tile_storage{};
    Entieties_graphics_storage entieties_storage{};
    Items_graphics_storage item_storage{};
    sf::RenderWindow window{};

    ~Graphics_manager() override = default;
private:
    void Set_view();

    void Render_inventory();
    void Render_items(sf::Vector2u size, sf::Font font);
    void Render_equipment(sf::Vector2u size, sf::Font font);
    void Render_stats(sf::Vector2u size, sf::Font font);

    sf::Vector2i render_area_start{};
    sf::Vector2i render_area_end{};

    sf::Texture tmp{};
    sf::Sprite drawer{tmp};
    Board_generator map_generator{100,100,&map};

    std::shared_ptr<Player> assign_player{};
};

}

#endif // CONOR_GRAPHICS_MANAGER_HPP
