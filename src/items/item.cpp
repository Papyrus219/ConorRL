#include "item.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using namespace conor;

int conor::Item::items_amount{0};

conor::Item::Item(std::string& stats_path)
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    name = stats_file["name"].get<std::string>();
    discription = stats_file["discription"].get<std::string>();
    capacity = stats_file["capacity"].get<int>();
}

conor::Item::Item(std::string && stats_path)
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    name = stats_file["name"].get<std::string>();
    discription = stats_file["discription"].get<std::string>();
    capacity = stats_file["capacity"].get<int>();
}


conor::Item::Item(int capacity_): capacity{capacity_}
{
    id = items_amount;
    items_amount++;
}

conor::Item::Item()
{
    id = items_amount;
    items_amount++;
}

bool conor::Item::operator==(const Item& other) const
{
    if(id == other.id) return true;

    return false;
}

conor::Item::~Item()
{
    items_amount--;
}
