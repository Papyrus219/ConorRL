#ifndef CONOR_PLAYER_MOVER_HPP
#define CONOR_PLAYER_MOVER_HPP

#include <SFML/System.hpp>
#include "../../board/board.hpp"
#include "./player_attacker.hpp"
#include "../../tools/subject.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Player_mover
{
public:
    Player_mover(Board* board, Player_attacker* attack): assign_board{board}, assign_attack{attack} {};
    void Move(Player *player, sf::Vector2f direction);
    Subject subject{};
private:
    Board* assign_board{};
    Player_attacker* assign_attack{};
};

}

#endif // CONOR_PLAYER_MOVER_H
