#include "player_interacter.hpp"
#include <iostream>

using namespace conor;

void conor::Player_interacter::Move( std::shared_ptr<Player> player, sf::Vector2f direction)
{
    if(direction == sf::Vector2f{0,0})
    {
        std::shared_ptr<Being> player_being = player;
        subject.Notify(Event::Player_moved, player_being );
        return;
    }

    sf::Vector2f position{player->possition};

    sf::Vector2i new_possition = static_cast<sf::Vector2i>(position + direction);

    if(new_possition.x < 0 || new_possition.x > assign_board->entities_map.size()-1) return;
    if(new_possition.y < 0 || new_possition.y > assign_board->entities_map[0].size()-1) return;

    if(assign_board->dungeon_map[new_possition.y][new_possition.x] == Tile::wall)
    {
        return;
    }
    if( !assign_board->entities_map[new_possition.y][new_possition.x].expired() )
    {
        Attack_melee(player,direction);
        return;
    }

    assign_board->entities_map[new_possition.y][new_possition.x] = player;
    assign_board->entities_map[position.y][position.x].reset();

    if(assign_board->dungeon_map[new_possition.y][new_possition.x] == Tile::exit)
    {
        std::cout << "You win!\n";
        std::exit(0);
    }

    player->possition = new_possition;
    std::shared_ptr<Being> player_being = player;
    subject.Notify(Event::Player_moved,player_being);
}

void conor::Player_interacter::Pick_up(std::shared_ptr<Player> player)
{
    sf::Vector2i poss = player->possition;
    if(assign_board->items_map[poss.y][poss.x].expired()) return;

    auto item = assign_board->items_map[poss.y][poss.x].lock();
    player->inventory->Add_item(item);
    assign_board->items_map[poss.y][poss.x].reset();
}

void conor::Player_interacter::Put_down(std::shared_ptr<Player> player)
{
    sf::Vector2i poss = player->possition;
    if(!assign_board->items_map[poss.y][poss.x].expired()) return;
    if(player->inventory->items.size() <= 0) return;

    auto item = ( player->inventory->items[ player->inventory->selected_item_index ] );
    assign_board->items_map[poss.y][poss.x] = item;
    item->possition = {poss.y, poss.x};
    player->inventory->Remove_item(item);
}

void conor::Player_interacter::Attack_melee(std::shared_ptr<Player> player, sf::Vector2f direction)
{
    sf::Vector2i atack_possition = player->possition + static_cast<sf::Vector2i>(direction);
    if(assign_board->entities_map[atack_possition.y][atack_possition.x].expired())
    {
        return;
    }

    std::shared_ptr<Being> being{};
    subject.Notify(Event::Player_atack,being);
    player->Fight(assign_board->entities_map[atack_possition.y][atack_possition.x].lock());

    if(assign_board->entities_map[atack_possition.y][atack_possition.x].lock()->stats.curr_health <= 0)
    {
        auto enemy_being = assign_board->entities_map[atack_possition.y][atack_possition.x].lock();
        auto enemy = std::dynamic_pointer_cast<Enemy>(enemy_being);

        if(assign_board->items_map[enemy->possition.y][enemy->possition.x].expired() && enemy->Get_drop_item())
        {
            enemy->Get_drop_item()->possition = {enemy->possition.y,enemy->possition.x};
            assign_board->items_map[enemy->possition.y][enemy->possition.x] = enemy->Get_drop_item();
        }

        subject.Notify(Event::Enemy_killed, enemy_being);
    }
    if(player->stats.curr_health <= 0)
    {
        std::cout << "You died!\n";
        std::exit(0);
    }
}

void conor::Player_interacter::Attack_range(std::shared_ptr<Player> player)
{

}

void conor::Player_interacter::Inventory_option_right(std::shared_ptr<Player> player)
{
    if(player->inventory->current_tab != InventoryTab::stats)
        player->inventory->current_tab = static_cast<InventoryTab>( static_cast<int>(player->inventory->current_tab) + 1 );
}

void conor::Player_interacter::Inventory_option_left(std::shared_ptr<Player> player)
{
    if(player->inventory->current_tab != InventoryTab::items)
        player->inventory->current_tab = static_cast<InventoryTab>( static_cast<int>(player->inventory->current_tab) - 1 );
}

void conor::Player_interacter::Inventory_item_option_up(std::shared_ptr<Player> player)
{
    player->inventory->selected_item_index--;
    if(player->inventory->selected_item_index < 0) player->inventory->selected_item_index = player->inventory->Get_items_amount()-1;
}

void conor::Player_interacter::Inventory_item_option_down(std::shared_ptr<Player> player)
{
    player->inventory->selected_item_index++;
    if(player->inventory->selected_item_index >= player->inventory->Get_items_amount()) player->inventory->selected_item_index = 0;
}

void conor::Player_interacter::Use_item(std::shared_ptr<Player> player)
{
    if(player->inventory->items.size() > 0) player->inventory->items[player->inventory->selected_item_index]->Use(*player);
}

void conor::Player_interacter::Inventory_equipment_option_up(std::shared_ptr<Player> player)
{
    if(player->inventory->selected_equipment_index > 0) player->inventory->selected_equipment_index--;
}

void conor::Player_interacter::Inventory_equipment_option_down(std::shared_ptr<Player> player)
{
    if(player->inventory->selected_equipment_index < 1) player->inventory->selected_equipment_index++;
}

void conor::Player_interacter::Dequip_selected_item(std::shared_ptr<Player> player)
{
    switch(player->inventory->selected_equipment_index)
    {
        case 0:
            player->Dequip(player->Get_const_armor());
            break;
        case 1:
            player->Dequip(player->Get_const_weapon());
            break;
    }
}

void conor::Player_interacter::Main_menu_option_up(std::shared_ptr<Player>)
{
    if(selected_main_menu_option > 0) selected_main_menu_option--;
}

void conor::Player_interacter::Main_menu_option_down(std::shared_ptr<Player> player)
{
    if(selected_main_menu_option < 1) selected_main_menu_option++;
}

void conor::Player_interacter::Main_menu_option_execute(std::shared_ptr<Player> player)
{
    switch(selected_main_menu_option)
    {
        case 0:
        {
            std::shared_ptr<Being> tmp{};
            subject.Notify(Event::Game_started, tmp);
            break;
        }
        case 1:
        {
            std::exit(0);
            break;
        }
    }
}
