#include "inventory.hpp"

using namespace conor;

bool conor::Inventory::Add_item(std::shared_ptr<Item> item)
{
    if(filling + item->Get_capacity() > capacity) return false;

    items.push_back(item);
    filling += item->Get_capacity();
    items_amount++;
    return true;
}

bool conor::Inventory::Remove_item(std::shared_ptr<Item> item)
{
    for(auto it = items.begin(); it != items.end(); it++)
    {
        if(*it == item)
        {
            items.erase(it);
            return true;
        }
    }

    return false;
}
