#include<iostream>

#include "./player/inventory/equipment.hpp"

int main()
{
    conor::Equipment sword{"../../data/equipment/weapons/basic_sword.json"};

    std::cout << sword.Get_discription() << '\n';

    return 0;
}
