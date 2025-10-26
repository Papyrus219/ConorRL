#ifndef CONOR_STATS_HPP
#define CONOR_STATS_HPP

#include<string>

namespace conor
{

enum class Stats
{
    health,
    speed,
    atack,
    defence,
};

Stats Stats_from_string(const std::string &s);
Stats Stats_from_string(const std::string &&s);

}

#endif
