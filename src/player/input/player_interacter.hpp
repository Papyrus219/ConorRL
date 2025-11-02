#ifndef CONOR_PLAYER_INTERACTER_HPP
#define CONOR_PLAYER_INTERACTER_HPP

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
    void Attack_range(std::shared_ptr<Player> player);

    void Inventory_option_left(std::shared_ptr<Player> player);
    void Inventory_option_right(std::shared_ptr<Player> player);

    void Inventory_item_option_up(std::shared_ptr<Player> player);
    void Inventory_item_option_down(std::shared_ptr<Player> player);
    void Use_item(std::shared_ptr<Player> player);

    void Inventory_equipment_option_up(std::shared_ptr<Player> player);
    void Inventory_equipment_option_down(std::shared_ptr<Player> player);
    void Dequip_selected_item(std::shared_ptr<Player> player);

    void Main_menu_option_up(std::shared_ptr<Player> player);
    void Main_menu_option_down(std::shared_ptr<Player> player);
    void Main_menu_option_execute(std::shared_ptr<Player> player);

    int Get_selected_main_menu_option() {return selected_main_menu_option;};

    Subject subject{};
private:
    Board* assign_board{};
    int selected_main_menu_option{};

    friend class Input_handler;
};

}

#endif // CONOR_PLAYER_INTERACTER_HPP
