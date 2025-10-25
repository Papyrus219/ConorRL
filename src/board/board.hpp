#ifndef CONOR_BOARD_HPP
#define CONOR_BOARD_HPP

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "./tile.hpp"
#include "../being.hpp"
#include "../player/player.hpp"
#include "../enemies/enemy.hpp"

namespace conor {

/**
 * @todo write docs
 */


class Board
{
public:
    Board();
    void Generate(Player* player, std::vector<Enemy*> &enemies);
    std::vector < std::vector<Tile> > dungeon_map{};
    std::vector < std::vector<Being*> > entities_map{};

    sf::Vector2f player_possition{};
private:
    constexpr static int map_heigh{100};
    constexpr static int map_width{100};
};

}

#endif // CONOR_BOARD_HPP
