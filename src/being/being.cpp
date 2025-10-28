#include "./being.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "../tools/subject.hpp"

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

/*
 * This function is a lie. It doesnt work, never did, and never will. Change that. This is fucking boolshit! Napraw gameplay! Albo ja naprawię ciebie!
 * -Papyrus219 z lekcji Polskiego.
 */

void conor::Being::Fight(std::shared_ptr<Being> oponent)
{
    Statistics* faster = &this->stats;
    Statistics* slower = &oponent->stats;

    if(slower->speed > faster->speed) std::swap(slower,faster);

    slower->curr_health -= ( (faster->atack*2) - (slower->defence) );
    std::cerr << "Slower: " << slower->curr_health << '\n';

    faster->curr_health -= ( (slower->atack*2) - (faster->defence) );
    std::cerr << "Faster: " << faster->curr_health << '\n';
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
