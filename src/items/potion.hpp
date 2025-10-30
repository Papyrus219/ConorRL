#ifndef CONOR_POTION_HPP
#define CONOR_POTION_HPP

#include <string>
#include <memory>
#include "./item.hpp"
#include "../being/stats.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Potion : public Item, public std::enable_shared_from_this<Potion>
{
public:
    Potion(std::string &stats_path);
    Potion(std::string &&stats_path);
    virtual void Use(Player & user) override;
private:
    Stats boosted_stat{};
    int boost_power{};
};

}

#endif // CONOR_POTION_HPP
