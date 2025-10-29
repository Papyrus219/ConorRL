#ifndef CONOR_ITEMS_GRAPHICS_STORAGE_HPP
#define CONOR_ITEMS_GRAPHICS_STORAGE_HPP

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../items/items_system.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Items_graphics_storage
{
public:
    void Set_item_tex(std::string items_tex_path, int categories_amount, std::vector<int> items_in_category_amount, sf::Vector2i item_size_ = {16,16});
    void Set_item_to_sptite(sf::Sprite &sprite, const std::shared_ptr<Item> item);
private:

    int Get_type_of_equipment(const std::shared_ptr<Equipment> equip);

    sf::Texture items_tex{};
    sf::Vector2i item_size{};
    std::vector < std::vector<sf::IntRect> > items_tex_possition{};
};

}

#endif // CONOR_ITEMS_GRAPHICS_STORAGE_HPP
