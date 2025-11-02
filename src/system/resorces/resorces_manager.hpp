#ifndef CONOR_RESORCES_MANAGER_HPP
#define CONOR_RESORCES_MANAGER_HPP

#include <memory>
#include "../../player/player.hpp"
#include "../../enemies/enemies_manager.hpp"
#include "../../items/item_manager.hpp"

namespace conor {

class Game;
class Graphics_manager;
class Logic_manager;

/**
 * @todo write docs
 */
class Resorces_manager
{
public:
    Resorces_manager();

    std::shared_ptr<Player> Get_player() {return player;};
    std::shared_ptr<Enemies_manager> Get_enemy_manager() {return enemy_manager;};
    std::shared_ptr<Item_manager> Get_item_manager() {return item_manager;};

    void Set_player(std::shared_ptr<Player> player_) { player = player_; };

    std::shared_ptr<Logic_manager> looper{};
    std::shared_ptr<Graphics_manager> renderer{};
private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemies_manager> enemy_manager{};
    std::shared_ptr<Item_manager> item_manager{};

    friend class Game;
};

}

#endif // CONOR_RESORCES_MANAGER_HPP
