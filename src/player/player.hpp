#ifndef CONOR_PLAYER_H
#define CONOR_PLAYER_H

#include <SFML/Graphics.hpp>
#include "./statitics.hpp"
#include "./inventory/item_system.hpp"

namespace conor
{

/**
* @todo write docs
*/
class Player
{
public:
    void Move(sf::Vector2i direction);
    void Equip(Equipment item);
    void Dequip(Equipment item);
    Statistics stats{};
private:
    sf::Vector2i Possition{};
    Equipment *equiped_armor{};
    Equipment *equiped_weapon{};
};

}

#endif // PLAYER_H
