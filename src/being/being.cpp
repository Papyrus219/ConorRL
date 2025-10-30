#include "./being.hpp"
#include "../tools/subject.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <algorithm>

conor::Being::Being(std::string& stats_path): stats{stats_path}
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    species = Spececies_from_string( stats_file["species"].get<std::string>() );
}

conor::Being::Being(std::string && stats_path): stats{stats_path}
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    species = Spececies_from_string( stats_file["species"].get<std::string>() );
}

void conor::Being::Fight(std::shared_ptr<Being> oponent)
{
    Statistics* faster = &this->stats;
    Statistics* slower = &oponent->stats;

    if(slower->speed > faster->speed) std::swap(slower,faster);

    slower->curr_health -= std::max( ( (faster->atack*2) - (slower->defence) ), 1 );

    if(slower->curr_health <= 0) return;

    faster->curr_health -= std::max( ( (slower->atack*2) - (faster->defence) ), 1 );
}

conor::Being::Species conor::Being::Spececies_from_string(const std::string& s)
{
    if(s == "player") return Species::player;
    if(s == "goblin") return Species::goblin;
    if(s == "skeleton") return Species::skieleton;

    throw std::invalid_argument{"Unknow type: " + s};
}

conor::Being::Species conor::Being::Spececies_from_string(const std::string && s)
{
    if(s == "player") return Species::player;
    if(s == "goblin") return Species::goblin;
    if(s == "skeleton") return Species::skieleton;

    throw std::invalid_argument{"Unknow type: " + s};
}
