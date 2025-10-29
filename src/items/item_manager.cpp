#include "item_manager.hpp"

using namespace conor;

void conor::Item_manager::Add_item(std::shared_ptr<Item>& item)
{
    for( auto &item_ : items)
        if(item_ == item) return;

    items.push_back(item);
}

void conor::Item_manager::Remove_item(std::shared_ptr<Item>& item)
{
    for(auto it = items.begin(); it != items.end();)
    {
        if(*it == item)
            it = items.erase(it);
        else
            it++;
    }
}

std::vector<std::weak_ptr<Item>> conor::Item_manager::Get_items()
{
    std::vector< std::weak_ptr<Item> > converted{};

    for(auto &item : items)
        converted.emplace_back( item );

    return converted;
}
