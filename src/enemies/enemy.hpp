#ifndef CONOR_ENEMY_H
#define CONOR_ENEMY_H

#include "../being/being.hpp"

namespace conor
{

/**
 * @todo write docs
 */
class Enemy : public Being
{
public:
    Enemy(Being::Species species_): Being{species_} {};
};

}

#endif // CONOR_ENEMY_H
