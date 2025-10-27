#ifndef CONOR_PLAYER_ATTACKER_H
#define CONOR_PLAYER_ATTACKER_H

#include "../../board/board.hpp"
#include "../player.hpp"
#include <memory>

namespace conor {

/**
 * @todo write docs
 */
class Player_attacker
{
public:
    Player_attacker(Board* board): assign_board{board} {};
    void Attack_melee(std::shared_ptr<Player> player,sf::Vector2f direction);
    void Attack_range();
private:
    Board* assign_board{};
};

}

#endif // CONOR_PLAYER_ATTACKER_H
