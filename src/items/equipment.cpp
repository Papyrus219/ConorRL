#include "equipment.hpp"
#include "../player/player.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using namespace conor;

conor::Equipment::Equipment(std::string &stats_path): Item{stats_path}
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    type = Type_from_string( stats_file["type"].get<std::string>() );
    boosted_stat = Stats_from_string( stats_file["stat"].get<std::string>() );
    boost_power = stats_file["power"].get<int>();

    spect = Specialisation::equipment;
}

conor::Equipment::Equipment(std::string &&stats_path): Item{stats_path}
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    type = Type_from_string( stats_file["type"].get<std::string>() );
    boosted_stat = Stats_from_string( stats_file["stat"].get<std::string>() );
    boost_power = stats_file["power"].get<int>();

    spect = Specialisation::equipment;
}

void conor::Equipment::Use(Player &player)
{
    player.Equip( std::make_shared<Equipment>(*this) );
}

namespace conor
{

Equip_type Type_from_string(const std::string &s)
{
    if(s == "weapon") return Equip_type::weapon;
    if(s == "armor") return Equip_type::armor;

    throw std::invalid_argument("Unknow type: " + s);
}


Equip_type Type_from_string(std::string &&s)
{
    if(s == "weapon") return Equip_type::weapon;
    if(s == "armor") return Equip_type::armor;

    throw std::invalid_argument("Unknow type: " + s);
}

}
