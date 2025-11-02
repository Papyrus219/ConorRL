#ifndef CONOR_INPUT_HANDLER_HPP
#define CONOR_INPUT_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include "../player.hpp"
#include "./player_interacter.hpp"

namespace conor
{

enum class Game_state;

/**
 * @todo write docs
 */
class Input_handler
{
public:
    Input_handler(const std::shared_ptr<Player> &assigned_player_): assigned_player{assigned_player_} {};

    void Handle_input(sf::Keyboard::Key &key, Game_state game_state);

    std::optional<Player_interacter> interacter;
private:

    void Handle_input_main_menu(sf::Keyboard::Key &key);
    void Handle_input_gameplay(sf::Keyboard::Key &key);
    void Handle_input_inventory(sf::Keyboard::Key &key);
    void Handle_input_board(sf::Keyboard::Key &key);
    void Handle_input_inventory_items(sf::Keyboard::Key &key);
    void Handle_input_inventory_equipment(sf::Keyboard::Key &key);
    void Handle_input_inventory_stats(sf::Keyboard::Key &key);

    const std::shared_ptr<Player> assigned_player{};
};

}

#endif // CONOR_INPUT_HANDLER_HPP
