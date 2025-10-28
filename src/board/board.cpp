#include "board.hpp"

using namespace conor;

conor::Board::Board()
{
    dungeon_map.resize(map_heigh, std::vector<Tile>(map_width, Tile::wall) );
    entities_map.resize(map_heigh, std::vector< std::weak_ptr<Being> >(map_width) );
}
