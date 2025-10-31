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
    for(int i=0; i <= items.size(); i++)
    {
        if(items[i]->Get_id() == item->Get_id())
        {
            items.erase(items.begin() + i);
            filling -= item->Get_capacity();
            items_amount--;
            if(selected_item_index == i && selected_item_index != 0) selected_item_index--;
            return true;
        }
    }

    return false;
}

std::vector<std::weak_ptr<Item>> conor::Inventory::Get_items()
{
    std::vector< std::weak_ptr<Item> > converted;
    for(auto &item : items)
        converted.push_back( item );

    return converted;
}
