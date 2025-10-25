#include "player_mover.hpp"

using namespace conor;

void conor::Player_mover::Move(Player* player, sf::Vector2f direction)
{
    sf::Vector2f position{player->possition};

    sf::Vector2i new_possition = static_cast<sf::Vector2i>(position + direction);

    if(new_possition.x < 0 || new_possition.x > assign_board->entities_map.size()-1) return;
    if(new_possition.y < 0 || new_possition.y > assign_board->entities_map[0].size()-1) return;

    if(assign_board->dungeon_map[new_possition.y][new_possition.x] == Tile::wall)
    {
        return;
    }
    if( assign_board->entities_map[new_possition.y][new_possition.x])
    {
        assign_attack->Attack_melee(player,direction);
        return;
    }

    assign_board->entities_map[new_possition.y][new_possition.x] = player;
    assign_board->entities_map[position.y][position.x] = nullptr;

    player->possition = new_possition;
    subject.Notify(Event::Player_moved,player);
}
