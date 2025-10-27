#include "player_attacker.hpp"
#include <iostream>

using namespace conor;

void conor::Player_attacker::Attack_melee(std::shared_ptr<Player> player, sf::Vector2f direction)
{
    sf::Vector2i atack_possition = player->possition + static_cast<sf::Vector2i>(direction);
    if(assign_board->entities_map[atack_possition.y][atack_possition.x].expired())
    {
        return;
    }

    player->Fight(assign_board->entities_map[atack_possition.y][atack_possition.x].lock());

    if(!player)
    {
        player = nullptr;
        std::cerr << "FATALITY!\n";
    }
}

void conor::Player_attacker::Attack_range()
{

}
