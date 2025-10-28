#ifndef CONOR_INVENTORY_HPP
#define CONOR_INVENTORY_HPP

#include <vector>
#include "./item.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Inventory
{
public:
    Inventory(int capacity_): capacity{capacity_} {};
    bool Add_item(Item *item);
    bool Remove_item(Item *item);

    int Get_filling() {return filling;};
    int Get_items_amount() {return items_amount;};

    const int capacity{};
private:
    int filling{};
    int items_amount{};
    std::vector<Item*> items{};
};

}

#endif // CONOR_INVENTORY_HPP
