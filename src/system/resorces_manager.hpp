#ifndef CONOR_RESORCES_MANAGER_HPP
#define CONOR_RESORCES_MANAGER_HPP

#include <memory>
#include "../player/player.hpp"
#include "../enemies/enemies_manager.hpp"
#include "../items/item_manager.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Resorces_manager
{
public:
    std::shared_ptr<Player> Get_player() {return player;};
    std::shared_ptr<Enemies_manager> Get_enemy_manager() {return enemy_manager;};
    std::shared_ptr<Item_manager> Get_item_manager() {return item_manager;};

private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemies_manager> enemy_manager{};
    std::shared_ptr<Item_manager> item_manager{};
};

}

#endif // CONOR_RESORCES_MANAGER_HPP
