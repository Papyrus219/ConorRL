#include "items_graphics_storage.hpp"
#include <iostream>

using namespace conor;

void conor::Items_graphics_storage::Set_item_tex(std::string items_tex_path, int categories_amount, std::vector<int> items_in_category_amount, sf::Vector2i item_size_)
{
    item_size = item_size_;

    if(items_tex.loadFromFile(items_tex_path))
    {
        items_tex_possition.clear();

        for(int i=0;i<categories_amount;i++)
        {
            items_tex_possition.push_back( std::vector<sf::IntRect>{} );
            for(int j=0;j<items_in_category_amount[i];j++)
            {
                items_tex_possition[i].push_back( {{item_size.x*j,item_size.y*i },{item_size.x,item_size.y}});
            }
        }
    }
    else
    {
        std::cerr << "Jesteś na Steam decku!\n";
    }
}

void conor::Items_graphics_storage::Set_item_to_sptite(sf::Sprite& sprite, const std::shared_ptr<Item> item )
{
    if (!item) {
        std::cerr << "Null item passed to Set_item_to_sprite!\n";
        return;
    }

    sprite.setTexture(items_tex);

    switch(item->spect)
    {
        case Item::trash:
            sprite.setTextureRect( items_tex_possition[0][0] );
            break;
        case Item::equipment:
            sprite.setTextureRect( items_tex_possition[1][  Get_type_of_equipment(std::dynamic_pointer_cast<Equipment>(item)) ] );
            break;
        case Item::potion:
            //TO ADD
            break;
        default:
            std::cerr << "Te synek ale zdefinuj ten typ itema!\n";
            break;
    }
}

int conor::Items_graphics_storage::Get_type_of_equipment(const std::shared_ptr<Equipment> equip)
{
    switch(equip->type)
    {
        case Equip_type::armor:
            return 0;
            break;
        case Equip_type::weapon:
            return 1;
            break;
        default:
            std::cerr << "Te synek ale zdefinuj ten typ itema!\n";
            break;
    }

    return 0;
}
