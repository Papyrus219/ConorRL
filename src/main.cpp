#include<iostream>

#include "./board/board.hpp"
#include "./board/board_generator.hpp"

int main()
{
    conor::Board map{};
    conor::Board_generator generator{100,100,&map.dungeon_map,&map.entities_map};

    generator.Generate();

    return 0;
}
