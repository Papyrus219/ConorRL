#include "player.hpp"

void conor::Player::Move(sf::Vector2i direction)
{
    if(possition.x - direction.x > 0 && possition.y - direction.y > 0)
    {
        possition -= direction;
    }
}

void conor::Player::Equip(std::shared_ptr<Equipment> item)
{
    switch(item->type)
    {
        case Equip_type::armor:
            if(equiped_armor)
            {
                if(item == equiped_armor) return;
                Dequip(equiped_armor);
            }

            equiped_armor = item;
            inventory.Remove_item(item);
            break;
        case Equip_type::weapon:
            if(equiped_weapon)
            {
                if(item == equiped_weapon) return;
                Dequip(equiped_weapon);
            }
            equiped_weapon = item;
            inventory.Remove_item(item);
            break;
    }

    switch(item->boosted_stat)
    {
        case Stats::defence:
            stats.defence += item->boost_power;
            break;
        case Stats::atack:
            stats.atack += item->boost_power;
            break;
        case Stats::health:
            stats.max_health += item->boost_power;
            break;
        case Stats::speed:
            stats.speed += item->boost_power;
            break;
    }
}

void conor::Player::Dequip(std::shared_ptr<Equipment> item)
{
    switch(item->type)
    {
        case Equip_type::armor:
            if(item != equiped_armor) return;
            if(equiped_armor)
            {
                inventory.Add_item(equiped_armor);
                equiped_armor = nullptr;
            }
        break;
        case Equip_type::weapon:
            if(item != equiped_weapon) return;
            if(equiped_weapon)
            {
                inventory.Add_item(equiped_weapon);
                equiped_weapon = nullptr;
            }
        break;
    }

    switch(item->boosted_stat)
    {
        case Stats::defence:
            stats.defence -= item->boost_power;
            break;
        case Stats::atack:
            stats.atack -= item->boost_power;
            break;
        case Stats::health:
            stats.max_health -= item->boost_power;
            break;
        case Stats::speed:
            stats.speed -= item->boost_power;
            break;
    }
}
