#include "resorces_manager.hpp"

using namespace conor;

conor::Resorces_manager::Resorces_manager()
{
    enemy_manager = std::make_shared<Enemies_manager>();
    item_manager = std::make_shared<Item_manager>();
}
