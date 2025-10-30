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
    if(!item) return;

    switch(item->type)
    {
        case Equip_type::armor:
            if(equiped_armor)
            {
                if(item->Get_id() == equiped_armor->Get_id()) return;
                Dequip(equiped_armor);
            }

            equiped_armor = item;
            inventory->Remove_item(item);
            break;
        case Equip_type::weapon:
            if(equiped_weapon)
            {
                if(item->Get_id() == equiped_weapon->Get_id()) return;
                Dequip(equiped_weapon);
            }

            equiped_weapon = item;
            inventory->Remove_item(item);
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
    if(!item) return;

    switch(item->type)
    {
        case Equip_type::armor:
            if(equiped_armor && item->Get_id() == equiped_armor->Get_id())
            {
                inventory->Add_item(equiped_armor);
                equiped_armor = nullptr;
            }
        break;
        case Equip_type::weapon:
            if(equiped_weapon && item->Get_id() == equiped_weapon->Get_id())
            {
                inventory->Add_item(equiped_weapon);
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
