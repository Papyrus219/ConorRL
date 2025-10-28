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


private:
    std::vector< std::shared_ptr<Item> > items{};
};

}

#endif // CONOR_ITEM_MANAGER_HPP
