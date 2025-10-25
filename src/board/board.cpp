#include "board.hpp"


using namespace conor;

conor::Board::Board()
{
    dungeon_map.resize(map_heigh, std::vector<Tile>(map_width, Tile::wall) );
    entities_map.resize(map_heigh, std::vector<Being*>(map_width,nullptr) );
}

void conor::Board::Generate(Player* player, std::vector<Enemy *>& enemies)
{

}
