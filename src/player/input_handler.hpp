#ifndef CONOR_INPUT_HANDLER_HPP
#define CONOR_INPUT_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include "./player.hpp"

namespace conor
{

/**
 * @todo write docs
 */
class Input_handler
{
public:
    Input_handler(Player *const assigned_player_): assigned_player{assigned_player_} {};
    void Key_input(sf::Keyboard::Key key) ;

private:
    Player *const assigned_player{};
};

}

#endif // CONOR_INPUT_HANDLER_H
