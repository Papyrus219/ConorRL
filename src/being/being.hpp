#ifndef CONOR_BEING_HPP
#define CONOR_BEING_HPP

#include <SFML/System/Vector2.hpp>
#include "./statitics.hpp"

namespace conor {

/**
 * @todo write docs
 */

struct Being
{
    enum Direction
    {
        up=0,
        down=1,
        left=2,
        right=3
    };

    enum Species
    {
        player=1,
        goblin=2,
        skieleton=3
    };

    Being(Species species_): species{species_}, stats{" "} {};

    Direction direction{};
    Species species{};
    sf::Vector2i possition{};
    Statistics stats;

private:

};

}

#endif // CONOR_BEING_HPP
