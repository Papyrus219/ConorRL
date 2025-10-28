#include "./being.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "../tools/subject.hpp"

conor::Subject conor::Being::subject{};

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

void conor::Being::Fight(std::shared_ptr<Being> oponent)
{
    Statistics* faster = &this->stats;
    Statistics* slower = &oponent->stats;

    if(slower->speed > faster->speed)
    {
        std::swap(slower,faster);
        std::cerr << "oponent is faster!\n";
    }

    slower->curr_health -= ( (faster->atack*2) - (slower->defence*3) );
    std::cerr << slower->curr_health << '\n';
    if(slower->curr_health <= 0)
    {
        std::cerr << "Slower one is dead!\n";
        subject.Notify(Event::Enemy_killed,oponent);

        return;
    }

    faster->curr_health -= ( (slower->atack*2) - (faster->defence*3) );
    std::cerr << faster->curr_health << '\n';
    if(faster->curr_health <= 0)
    {
        std::cerr << "Slower one is dead!\n";
        return;
    }
}
