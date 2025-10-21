#include "board.hpp"


using namespace conor;

conor::Board::Board()
{
    map.resize(map_heigh, std::vector<Tile>(map_width, Tile::wall) );
}

void conor::Board::Generate()
{

}
