#ifndef CONOR_ITEM_MANAGER_HPP
#define CONOR_ITEM_MANAGER_HPP

#include "./item.hpp"
#include <memory>
#include <vector>

namespace conor {

/**
 * @todo write docs
 */
class Item_manager
{
public:
    void Add_item(std::shared_ptr<Item> &item);
    void Remove_item(std::shared_ptr<Item> &item);
    std::vector< std::weak_ptr<Item> > Get_items();
    std::vector< std::shared_ptr<Item> >* Get_items_ptr() {return &items;};

private:
    std::vector< std::shared_ptr<Item> > items{};
};

}

#endif // CONOR_ITEM_MANAGER_HPP
