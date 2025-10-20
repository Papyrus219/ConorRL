#include "item.hpp"

using namespace conor;

conor::Item::Item(int capacity_, int id_): capacity{capacity_}, id{id_}
{

}

bool conor::Item::operator==(const Item& other) const
{
    if(id == other.id) return true;

    return false;
}
