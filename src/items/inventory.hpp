#ifndef CONOR_INVENTORY_HPP
#define CONOR_INVENTORY_HPP

#include <vector>
#include <memory>
#include "./item.hpp"

namespace conor {

class Player_interacter;

enum class InventoryTab
{
    items=0,
    equipment=1,
    stats=2
};

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
    int Get_selected_item_index() {return selected_item_index;};
    int Get_selected_equipment_index() {return selected_equipment_index;};
    InventoryTab Get_current_tab() {return current_tab;};
    std::vector< std::weak_ptr<Item> > Get_items();

    const int capacity{};
private:
    int filling{};
    int items_amount{};
    int selected_item_index{};
    int selected_equipment_index{};

    InventoryTab current_tab = InventoryTab::items;
    std::vector< std::shared_ptr<Item> > items{};

    friend Player_interacter;
};

}

#endif // CONOR_INVENTORY_HPP
