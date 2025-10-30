#include "item.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using namespace conor;

unsigned int conor::Item::items_amount{0};

conor::Item::Item(std::string& stats_path): id{items_amount}
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    name = stats_file["name"].get<std::string>();
    discription = stats_file["discription"].get<std::string>();
    capacity = stats_file["capacity"].get<int>();

    items_amount++;
    coutable = true;
}

conor::Item::Item(std::string && stats_path): id{items_amount}
{
    using nlohmann::json;
    json stats_file{};
    std::ifstream file{stats_path};
    file >> stats_file;
    file.close();

    name = stats_file["name"].get<std::string>();
    discription = stats_file["discription"].get<std::string>();
    capacity = stats_file["capacity"].get<int>();

    items_amount++;
    coutable = true;
}


conor::Item::Item(int capacity_): capacity{capacity_}, id{items_amount}
{
    items_amount++;
    coutable = true;
}

conor::Item::Item(): id{items_amount}
{
    items_amount++;
    coutable = true;
}

conor::Item::Item(const Item& other): id{other.id}
{
    this->possition = other.possition;
    this->picked = other.picked;
    this->name = other.name;
    this->discription = other.discription;
    this->capacity = other.capacity;
    this->spect = other.spect;

    coutable = false;
}

conor::Item::Item(Item && other): id{other.id}
{
    this->possition = other.possition;
    this->picked = other.picked;
    this->name = other.name;
    this->discription = other.discription;
    this->capacity = other.capacity;
    this->spect = other.spect;

    coutable = false;
}

Item & conor::Item::operator=(const Item& other)
{
    if(this == &other) return *this;

    this->possition = other.possition;
    this->picked = other.picked;
    this->name = other.name;
    this->discription = other.discription;
    this->capacity = other.capacity;
    this->spect = other.spect;
    return *this;
}

bool conor::Item::operator==(const Item& other) const
{
    return id == other.id;
}

conor::Item::~Item()
{
    if(coutable) items_amount--;
}
