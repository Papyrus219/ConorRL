#include "player.hpp"

void conor::Player::Move(sf::Vector2i direction)
{
    if(Possition.x - direction.x > 0 && Possition.y - direction.y > 0)
    {
        Possition -= direction;
    }
}

void conor::Player::Equip(Equipment item)
{
    switch(item.type)
    {
        case Equip_type::armor:
            if(equiped_armor)   Dequip(*equiped_armor);
            equiped_armor = &item;
            break;
        case Equip_type::weapon:
            if(equiped_weapon)  Dequip(*equiped_weapon);
            equiped_weapon = &item;
            break;
    }

    switch(item.boosted_stat)
    {
        case Stats::defence:
            stats.defence += item.boost_power;
            break;
        case Stats::atack:
            stats.atack += item.boost_power;
            break;
        case Stats::health:
            stats.max_health += item.boost_power;
            break;
        case Stats::speed:
            stats.speed += item.boost_power;
            break;
    }
}

void conor::Player::Dequip(Equipment item)
{
    switch(item.type)
    {
        case Equip_type::armor:
            if(equiped_armor) equiped_armor = nullptr;
        break;
        case Equip_type::weapon:
            if(equiped_weapon)  equiped_weapon = nullptr;
        break;
    }

    switch(item.boosted_stat)
    {
        case Stats::defence:
            stats.defence -= item.boost_power;
            break;
        case Stats::atack:
            stats.atack -= item.boost_power;
            break;
        case Stats::health:
            stats.max_health -= item.boost_power;
            break;
        case Stats::speed:
            stats.speed -= item.boost_power;
            break;
    }
}
