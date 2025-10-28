#include "./statitics.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

conor::Statistics::Statistics(std::string& stats_path)
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    max_health = stats_file["health"].get<int>();
    curr_health = max_health;
    speed = stats_file["speed"].get<int>();
    atack = stats_file["atack"].get<int>();
    defence = stats_file["defence"].get<int>();
}

conor::Statistics::Statistics(std::string&& stats_path)
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    max_health = stats_file["health"].get<int>();
    curr_health = max_health;
    speed = stats_file["speed"].get<int>();
    atack = stats_file["atack"].get<int>();
    defence = stats_file["defence"].get<int>();
}
