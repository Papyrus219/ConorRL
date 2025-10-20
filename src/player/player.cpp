#include "player.hpp"

void conor::Player::Move(sf::Vector2i direction)
{
    if(Possition.x - direction.x > 0 && Possition.y - direction.y > 0)
    {
        Possition -= direction;
    }
}
