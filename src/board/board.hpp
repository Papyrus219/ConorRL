#ifndef CONOR_BOARD_HPP
#define CONOR_BOARD_HPP

#include<vector>

namespace conor {

/**
 * @todo write docs
 */

enum class Tile
{
    wall,
    floor
};

class Board
{
    Board();

    void Generate();

    constexpr static int map_heigh{100};
    constexpr static int map_width{100};
    constexpr static int min_leaf_size{10};
    constexpr static int max_leaf_size{20};

    std::vector < std::vector<Tile> > map{};

};

}

#endif // CONOR_BOARD_HPP
