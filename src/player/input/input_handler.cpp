#include "input_handler.hpp"
#include <iostream>

void conor::Input_handler::Handle_input_broad(sf::Keyboard::Key &key)
{
    if(assigned_player->in_inventory)
    {
        Handle_input_inventory(key);
    }
    else
    {
        Handle_input_board(key);
    }
}

void conor::Input_handler::Handle_input_board(sf::Keyboard::Key& key)
{
    using sf::Keyboard::Key;

    switch(key)
    {
        case Key::Right:
            assigned_player->direction = Being::right;
            interacter->Move(assigned_player,{1,0});
            break;
        case Key::Left:
            assigned_player->direction = Being::left;
            interacter->Move(assigned_player,{-1,0});
            break;
        case Key::Up:
            assigned_player->direction = Being::up;
            interacter->Move(assigned_player,{0,-1});
            break;
        case Key::Down:
            assigned_player->direction = Being::down;
            interacter->Move(assigned_player,{0,1});
            break;
        case Key::Space:
            interacter->Move(assigned_player,{0,0});
            break;
        case Key::I:
            std::cerr << "Open inventory!\n";
            assigned_player->in_inventory = true;
            break;
        case Key::P:
            interacter->Pick_up(assigned_player);
        default:
            break;
    }
}

void conor::Input_handler::Handle_input_inventory(sf::Keyboard::Key& key)
{
    using sf::Keyboard::Key;

    switch(key)
    {
        case Key::Up:
            interacter->Inventory_option_up(assigned_player);
            break;
        case Key::Down:
            interacter->Inventory_option_down(assigned_player);
            break;
        case Key::Enter:
            interacter->Use_item(assigned_player);
            break;
        case Key::I:
            assigned_player->in_inventory = false;
            break;
        default:
            break;
    }
}
