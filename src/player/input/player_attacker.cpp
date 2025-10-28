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

    if(assign_board->entities_map[atack_possition.y][atack_possition.x].lock()->stats.curr_health <= 0)
    {
        std::cerr << "Enemy down!\n";
        auto enemy = assign_board->entities_map[atack_possition.y][atack_possition.x].lock();
        subject.Notify(Event::Enemy_killed, enemy);
    }
    if(player->stats.curr_health <= 0)
    {
        std::cerr << "FATALITY!\n";
        std::exit(0);
    }


}

void conor::Player_attacker::Attack_range()
{

}
