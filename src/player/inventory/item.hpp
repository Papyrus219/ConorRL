#ifndef CONOR_ITEM_HPP
#define CONOR_ITEM_HPP

namespace conor {

/**
 * @todo write docs
 */
class Item
{
public:
    Item(int capacity_, int id_);
    Item(const Item &other) = default;
    Item(Item &&other) = default;
    virtual void Use() = 0;
    bool operator==(const Item& other) const;

    int Get_capacity() {return capacity;};
    int Get_id() {return id;};

    virtual ~Item() = default;
private:
    int capacity{};
    int id{};
};

}

#endif // CONOR_ITEM_HPP
