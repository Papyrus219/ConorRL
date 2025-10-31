#include "enemy.hpp"
#include "../items/items_system.hpp"
#include <random>

using namespace conor;

conor::Enemy::Enemy(Being::Species species_, std::vector< std::shared_ptr<Item> > &items): Being{species_}
{
    Roll_drop_item(items);
}

conor::Enemy::Enemy(std::string& stats_path, std::vector< std::shared_ptr<Item> > &items): Being{stats_path}
{
    Roll_drop_item(items);
}

conor::Enemy::Enemy(std::string && stats_path, std::vector< std::shared_ptr<Item> > &items): Being{stats_path}
{
    Roll_drop_item(items);
}

void conor::Enemy::Roll_drop_item(std::vector< std::shared_ptr<Item> > &items)
{
    std::uniform_int_distribution<int> item_select{0,20};
    std::uniform_int_distribution<int> random_power{1,7};

    int result{ item_select(rng) };

    if(result > 10)
    {

    }
    else if(result > 5)
    {
        drop_item = std::make_shared<Potion>("../../data/potions/health_potion.json");
        items.push_back(drop_item);
    }
    else if(result > 2)
    {
        drop_item = std::make_shared<Equipment>("../../data/equipment/weapons/basic_sword.json");

        auto drop_item_eq = std::dynamic_pointer_cast<Equipment>(drop_item);
        drop_item_eq->boost_power = random_power(rng);

        items.push_back(drop_item);
    }
    else
    {
        drop_item = std::make_shared<Equipment>("../../data/equipment/armor/basic_armor.json");\
        auto drop_item_eq = std::dynamic_pointer_cast<Equipment>(drop_item);
        drop_item_eq->boost_power = random_power(rng);
        items.push_back(drop_item);
    }
}
