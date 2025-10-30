#ifndef CONOR_ENEMY_H
#define CONOR_ENEMY_H

#include "../being/being.hpp"
#include <memory>
#include <random>

namespace conor
{

class Item;

/**
 * @todo write docs
 */
class Enemy : public Being
{
public:
    Enemy(Being::Species species_, std::vector< std::shared_ptr<Item> > &items);
    Enemy(std::string &stats_path, std::vector< std::shared_ptr<Item> > &items);
    Enemy(std::string &&stats_path, std::vector< std::shared_ptr<Item> > &items);

    std::shared_ptr<Item> Get_drop_item() {return drop_item;};

private:
    void Roll_drop_item(std::vector< std::shared_ptr<Item> > &items);

    std::shared_ptr<Item> drop_item{};
    std::random_device rand{};
    std::mt19937 rng{rand()};
};

}

#endif // CONOR_ENEMY_H
