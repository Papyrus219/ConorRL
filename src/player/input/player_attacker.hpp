#ifndef CONOR_PLAYER_ATTACKER_HPP
#define CONOR_PLAYER_ATTACKER_HPP

#include "../../board/board.hpp"
#include "../player.hpp"
#include "../../tools/subject.hpp"
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

    Subject subject{};
private:
    Board* assign_board{};
};

}

#endif // CONOR_PLAYER_ATTACKER_HPP
