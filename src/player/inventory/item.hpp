#ifndef CONOR_ITEM_HPP
#define CONOR_ITEM_HPP

#include <string>

namespace conor {

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
    Item(const Item &other) = default;
    Item(Item &&other) = default;
    virtual void Use() = 0;
    bool operator==(const Item& other) const;

    std::string Get_name() {return name;};
    std::string Get_discription() {return discription;};
    int Get_capacity() {return capacity;};
    int Get_id() {return id;};

    virtual ~Item();
protected:
    std::string name{};
    std::string discription{};
    int capacity{};
    int id{};

    static int items_amount;
};

}

#endif // CONOR_ITEM_HPP
