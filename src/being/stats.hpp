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

Stats Stats_from_string(std::string &s);
Stats Stats_from_string(std::string &&s);

}

#endif
