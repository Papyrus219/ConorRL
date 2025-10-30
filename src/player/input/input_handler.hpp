#ifndef CONOR_INPUT_HANDLER_HPP
#define CONOR_INPUT_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include "../player.hpp"
#include "./player_interacter.hpp"

namespace conor
{

/**
 * @todo write docs
 */
class Input_handler
{
public:
    Input_handler(const std::shared_ptr<Player> &assigned_player_): assigned_player{assigned_player_} {};

    void Handle_input_broad(sf::Keyboard::Key &key);
    void Handle_input_inventory(sf::Keyboard::Key &key);
    void Handle_input_board(sf::Keyboard::Key &key);

    std::optional<Player_interacter> interacter;
private:
    const std::shared_ptr<Player> assigned_player{};
};

}

#endif // CONOR_INPUT_HANDLER_HPP
