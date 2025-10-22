#ifndef CONOR_BOARD_HPP
#define CONOR_BOARD_HPP

#include <vector>
#include "./tile.hpp"

namespace conor {

/**
 * @todo write docs
 */


class Board
{
public:
    Board();
    void Generate();
    std::vector < std::vector<Tile> > dungeon_map{};
    std::vector < std::vector<Entities> > entities_map{};

private:
    constexpr static int map_heigh{100};
    constexpr static int map_width{100};
};

}

#endif // CONOR_BOARD_HPP
