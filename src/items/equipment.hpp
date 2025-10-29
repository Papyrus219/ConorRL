#ifndef CONOR_EQUIPMENT_HPP
#define CONOR_EQUIPMENT_HPP


#include <string>
#include "./item.hpp"
#include "../being/stats.hpp"
namespace conor {

enum class Equip_type
{
    weapon,
    armor
};

/**
 * @todo write docs
 */
class Equipment : public Item
{
public:
    Equipment(std::string &stats_path);
    Equipment(std::string &&stats_path);
    virtual void Use(Player &player) override;

    Stats boosted_stat{};
    int boost_power{};
    Equip_type type{};
};

Equip_type Type_from_string(std::string &s);
Equip_type Type_from_string(std::string &&s);

}

#endif // CONOR_EQUIPMENT_HPP
