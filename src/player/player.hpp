#ifndef CONOR_PLAYER_H
#define CONOR_PLAYER_H

#include <SFML/Graphics.hpp>

namespace conor
{

/**
* @todo write docs
*/
class Player
{
public:
    void Move(sf::Vector2i direction);
private:
    sf::Vector2i Possition{};
};

}

#endif // PLAYER_H
