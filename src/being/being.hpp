#ifndef CONOR_BEING_HPP
#define CONOR_BEING_HPP

#include <SFML/System/Vector2.hpp>
#include <memory>
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

    Being() = default;
    Being(Species species_): species{species_}, stats{} {};
    Being(std::string &stats_path);
    Being(std::string &&stats_path);

    void Fight( std::shared_ptr<Being> oponent);

    Direction direction{};
    Species species{};
    sf::Vector2i possition{};
    Statistics stats;

    virtual ~Being() = default;
private:
    Species Spececies_from_string(const std::string &s);
    Species Spececies_from_string(const std::string &&s);
};

}

#endif // CONOR_BEING_HPP
