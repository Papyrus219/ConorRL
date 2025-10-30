#ifndef CONOR_PLAYER_MOVER_HPP
#define CONOR_PLAYER_MOVER_HPP

#include <SFML/System.hpp>
#include "../../board/board.hpp"
#include "../../tools/subject.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Player_interacter
{
public:
    Player_interacter(Board* board): assign_board{board} {};
    void Move(std::shared_ptr<Player> player, sf::Vector2f direction);
    void Pick_up(std::shared_ptr<Player> player);
    void Put_down(std::shared_ptr<Player> player);

    void Attack_melee(std::shared_ptr<Player> player,sf::Vector2f direction);
    void Attack_range();

    Subject subject{};
private:
    Board* assign_board{};
};

}

#endif // CONOR_PLAYER_MOVER_H
