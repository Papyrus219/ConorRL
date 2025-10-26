#include "./statitics.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

conor::Statistics::Statistics(std::string& stats_path)
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    if (!file.is_open()) {
        std::cerr << "❌ Nie mogę otworzyć pliku: " << stats_path << std::endl;
        throw std::runtime_error("Nie można otworzyć pliku JSON: " + stats_path);
    }

    try {
        file >> stats_file;
    } catch (const std::exception& e) {
        std::cerr << "⚠️ Błąd parsowania JSON w " << stats_path << ": " << e.what() << std::endl;
        throw;
    }
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
    if (!file.is_open()) {
        std::cerr << "❌ Nie mogę otworzyć pliku: " << stats_path << std::endl;
        throw std::runtime_error("Nie można otworzyć pliku JSON: " + stats_path);
    }

    try {
        file >> stats_file;
    } catch (const std::exception& e) {
        std::cerr << "⚠️ Błąd parsowania JSON w " << stats_path << ": " << e.what() << std::endl;
        throw;
    }
    file.close();

    max_health = stats_file["health"].get<int>();
    curr_health = max_health;
    speed = stats_file["speed"].get<int>();
    atack = stats_file["atack"].get<int>();
    defence = stats_file["defence"].get<int>();
}
