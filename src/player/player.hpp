#ifndef CONOR_PLAYER_H
#define CONOR_PLAYER_H

#include <SFML/Graphics.hpp>
#include "../being/being.hpp"
#include "../being/statitics.hpp"
#include "./inventory/item_system.hpp"

namespace conor
{

class Input_handler;
class Player_mover;

/**
* @todo write docs
*/
class Player: public Being
{
public:;
    Player(Species species_): Being{species_} {};
    Player(std::string &stats_path): Being{stats_path} {};
    Player(std::string &&stats_path): Being{stats_path} {};

    void Move(sf::Vector2i direction);
    void Equip(Equipment item);
    void Dequip(Equipment item);
private:
    Equipment *equiped_armor{};
    Equipment *equiped_weapon{};
    bool in_inventory{};

    friend Input_handler;
    friend Player_mover;
};

}

#endif // PLAYER_H
