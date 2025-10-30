#ifndef CONOR_PLAYER_H
#define CONOR_PLAYER_H

#include <SFML/Graphics.hpp>
#include "../being/being.hpp"
#include "../being/statitics.hpp"
#include "../items/inventory.hpp"
#include "../items/equipment.hpp"

namespace conor
{

class Input_handler;
class Player_interacter;

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
    void Equip(std::shared_ptr<Equipment> item);
    void Dequip(std::shared_ptr<Equipment> item);

    bool Get_if_in_inventory() {return in_inventory;};
    const std::shared_ptr<Inventory> Get_const_inventory() const {return inventory;};
    const std::shared_ptr<Equipment> Get_const_weapon() const {return equiped_weapon;};
    const std::shared_ptr<Equipment> Get_const_armor() const {return equiped_armor;};

private:
    std::shared_ptr<Inventory> inventory{ std::make_shared<Inventory>(20) };
    std::shared_ptr<Equipment> equiped_armor{};
    std::shared_ptr<Equipment> equiped_weapon{};
    bool in_inventory{};

    friend Input_handler;
    friend Player_interacter;
};

}

#endif // PLAYER_H
