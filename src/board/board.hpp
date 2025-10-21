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
public:
    Board();
    void Generate();
    std::vector < std::vector<Tile> > map{};

private:
    constexpr static int map_heigh{100};
    constexpr static int map_width{100};
};

}

#endif // CONOR_BOARD_HPP
