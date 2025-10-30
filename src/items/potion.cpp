#include "potion.hpp"
#include "../player/player.hpp"
#include <algorithm>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace conor;

conor::Potion::Potion(std::string& stats_path): Item{stats_path}
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    boosted_stat = Stats_from_string( stats_file["stat"].get<std::string>() );
    boost_power = stats_file["power"].get<int>();

    spect = potion;
}

conor::Potion::Potion(std::string && stats_path): Item{stats_path}
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    boosted_stat = Stats_from_string( stats_file["stat"].get<std::string>() );
    boost_power = stats_file["power"].get<int>();

    spect = potion;
}

void conor::Potion::Use(Player& user)
{
    switch(boosted_stat)
    {
        case Stats::health:
            user.stats.curr_health = std::min( (user.stats.curr_health + boost_power), user.stats.max_health );
            break;
        case Stats::atack:
            user.stats.atack += boost_power;
            break;
        case Stats::defence:
            user.stats.defence += boost_power;
            break;
        case Stats::speed:
            user.stats.speed += boost_power;
            break;
    }

    user.Get_const_inventory()->Remove_item( shared_from_this() );
}
