#include "input_handler.hpp"

void conor::Input_handler::Key_input(sf::Keyboard::Key key)
{
    using sf::Keyboard::Key;

    switch(key)
    {
        case Key::Left:
            assigned_player->Move({-1,0});
        case Key::Right:
            assigned_player->Move({1,0});
        case Key::Up:
            assigned_player->Move({0,1});
        case Key::Down:
            assigned_player->Move({0,-1});

    }
}
