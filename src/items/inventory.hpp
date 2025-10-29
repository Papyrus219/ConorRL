#ifndef CONOR_INVENTORY_HPP
#define CONOR_INVENTORY_HPP

#include <vector>
#include <memory>
#include "./item.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Inventory
{
public:
    Inventory(int capacity_): capacity{capacity_} {};
    bool Add_item(std::shared_ptr<Item> item);
    bool Remove_item(std::shared_ptr<Item> item);

    int Get_filling() {return filling;};
    int Get_items_amount() {return items_amount;};
    const std::vector< std::shared_ptr<Item> > Get_items_ptr_const() const {return items;};

    const int capacity{};
private:
    int filling{};
    int items_amount{};
    std::vector< std::shared_ptr<Item> > items{};
};

}

#endif // CONOR_INVENTORY_HPP
