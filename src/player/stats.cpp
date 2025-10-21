#include "./stats.hpp"

using namespace conor;
#include<stdexcept>

namespace conor
{
    Stats Stats_from_string(const std::string &s)
    {
        if(s == "health") return Stats::health;
        if(s == "speed") return Stats::speed;
        if(s == "atack") return Stats::atack;
        if(s == "defence") return Stats::defence;

        throw std::invalid_argument("Unknow type: " + s);
    }

    Stats Stats_from_string(std::string &&s)
    {
        if(s == "health") return Stats::health;
        if(s == "speed") return Stats::speed;
        if(s == "atack") return Stats::atack;
        if(s == "defence") return Stats::defence;

        throw std::invalid_argument("Unknow type: " + s);
    }
}


