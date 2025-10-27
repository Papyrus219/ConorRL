#ifndef CONOR_BOARD_HPP
#define CONOR_BOARD_HPP

#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "./tile.hpp"
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
    std::vector < std::vector<Tile> > dungeon_map{};
    std::vector < std::vector< std::weak_ptr<Being> > > entities_map{};

    sf::Vector2f player_possition{};
private:
    constexpr static int map_heigh{100};
    constexpr static int map_width{100};
};

}

#endif // CONOR_BOARD_HPP
