#ifndef CONOR_ITEM_HPP
#define CONOR_ITEM_HPP

#include <string>
#include <SFML/System/Vector2.hpp>

namespace conor {

class Player;

/**
 * @todo write docs
 */
class Item
{
public:
    Item();
    Item(std::string &stats_path);
    Item(std::string &&stats_path);
    Item(int capacity_);
    Item(const Item &other);
    Item(Item &&other);

    std::string Get_name() {return name;};
    std::string Get_discription() {return discription;};
    int Get_capacity() {return capacity;};
    int Get_id() {return id;};

    Item& operator=(const Item& other);
    bool operator==(const Item& other) const;

    virtual void Use(Player &user) = 0;

    sf::Vector2i possition{};
    bool picked{};

    enum Specialisation
    {
        trash = 0,
        equipment = 1,
        potion = 2
    };

    Specialisation spect{};

    virtual ~Item();
protected:
    std::string name{};
    std::string discription{};
    int capacity{};
    unsigned int id{};
    bool coutable{};

    static unsigned int items_amount;
};

}

#endif // CONOR_ITEM_HPP
