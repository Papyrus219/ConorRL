#include "input_handler.hpp"

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
            mover->Move(assigned_player,{1,0});
            break;
        case Key::Left:
            assigned_player->direction = Being::left;
            mover->Move(assigned_player,{-1,0});
            break;
        case Key::Up:
            assigned_player->direction = Being::up;
            mover->Move(assigned_player,{0,-1});
            break;
        case Key::Down:
            assigned_player->direction = Being::down;
            mover->Move(assigned_player,{0,1});
            break;
        default:
            break;
    }
}

void conor::Input_handler::Handle_input_inventory(sf::Keyboard::Key& key)
{

}
