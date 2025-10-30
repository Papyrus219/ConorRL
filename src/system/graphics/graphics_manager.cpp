#include "./graphics_manager.hpp"
#include <algorithm>
#include <iostream>

using namespace conor;

void conor::Graphics_manager::Init_window(sf::Vector2u size)
{
    window.create(sf::VideoMode{{size.x , size.y}}, "ConorRL",sf::Style::Titlebar | sf::Style::Close);
    render_area_start = {0,0};
    render_area_end = {static_cast<int> (size.x/100)+1 , static_cast<int>(size.y/100)+1 };

    Set_view();
}

void conor::Graphics_manager::Generate_map(std::shared_ptr<Player> &player, std::vector< std::shared_ptr<Enemy> > *enemies, std::vector< std::shared_ptr<Item> > *items)
{
    map_generator.enemies = enemies;
    map_generator.items = items;
    map_generator.Generate(player);
}

void conor::Graphics_manager::Set_view()
{
    sf::View view{};

    sf::Vector2f title_size = static_cast<sf::Vector2f>( tile_storage.Get_tile_size() );
    sf::Vector2i visible_tiles = { render_area_end - render_area_start };

    view.setSize( {title_size.x * visible_tiles.x, title_size.y * visible_tiles.y} );
    view.setCenter( {(title_size.x * visible_tiles.x) / 2.f, (title_size.y * visible_tiles.y) / 2.f } );

    window.setView(view);
    Update();
}

void conor::Graphics_manager::Resize()
{
    sf::Vector2u size = window.getSize();

    render_area_end = {static_cast<int> (size.x/100)+1 , static_cast<int>(size.y/100)+1 };
    Set_view();
}

void conor::Graphics_manager::Render()
{
    sf::Vector2f tile_size = static_cast<sf::Vector2f>( tile_storage.Get_tile_size() );

    int limiter_y = std::min( static_cast<int>( map.dungeon_map.size() ) , render_area_end.y );
    int limiter_x = std::min( static_cast<int>( map.dungeon_map[0].size() ), render_area_end.x );

    window.clear();
    for(int y = render_area_start.y; y < limiter_y; y++)
    {
        for(int x = render_area_start.x; x < limiter_x; x++)
        {
            int pos_x{x-render_area_start.x}, pos_y{y-render_area_start.y};
            drawer.setPosition( {tile_size.x*pos_x, tile_size.y*pos_y} );

            switch(map.dungeon_map[y][x])
            {
                case Tile::floor:
                    tile_storage.Set_tile_to_sprite(drawer,0);
                    break;
                case Tile::wall:
                    tile_storage.Set_tile_to_sprite(drawer,1);
                    break;
                case Tile::exit:
                    tile_storage.Set_tile_to_sprite(drawer,2);
                    break;
            }
            window.draw(drawer);

            if(!map.items_map[y][x].expired())
            {
                auto to_set{map.items_map[y][x].lock()};
                item_storage.Set_item_to_sptite(drawer,to_set);
                window.draw(drawer);
            }

            if(!map.entities_map[y][x].expired())
            {
                auto to_set{map.entities_map[y][x].lock()};
                entieties_storage.Set_tile_to_sprite(drawer,to_set->species,to_set->direction);
                window.draw(drawer);
            }
        }
    }

    if(assign_player->Get_if_in_inventory()) Render_inventory();

    window.display();
}

void conor::Graphics_manager::Render_inventory()
{
    if(!assign_player) return;
    auto inventory = assign_player->Get_const_inventory();

    sf::Vector2u size = window.getSize();
    window.setView( window.getDefaultView() );

    float ITEM_SPACING = 60.f;
    float LEFT_MARGIN = (size.x*0.2) + 20.f;
    float TOP_MARGIN = (size.y*0.2) + 100.f;

    sf::RectangleShape background({size.x*0.7f, size.y*0.7f});
    background.setFillColor(sf::Color{128,10,10,150});
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(4.f);

    background.setPosition({size.x*0.2f, size.y*0.2f});
    window.draw(background);

    sf::Font font;
    if(!font.openFromFile("../../data/fonts/font1.ttf"))
    {
        std::cerr << "Jesteś na steam decku!\n";
    }

    sf::Text items_tab{font, "[1] Items",22};
    sf::Text equipment_tab{font,"[2] Equipment",22};
    sf::Text stats_tab{font,"[3] Stats",22};

    float tab_y = size.y * 0.22f;
    items_tab.setPosition( {size.x * 0.25f, tab_y} );
    equipment_tab.setPosition( {size.x * 0.40f, tab_y} );
    stats_tab.setPosition( {size.x * 0.58f, tab_y} );

    sf::Color gray = sf::Color{180,180,180,130};
    items_tab.setFillColor(gray);
    equipment_tab.setFillColor(gray);
    stats_tab.setFillColor(gray);

    switch(inventory->Get_current_tab())
    {
        case InventoryTab::items:
            items_tab.setFillColor(sf::Color::White);
            break;
        case InventoryTab::equipment:
            equipment_tab.setFillColor(sf::Color::White);
            break;

        case InventoryTab::stats:
            stats_tab.setFillColor(sf::Color::White);
            break;
    }

    window.draw(items_tab);
    window.draw(equipment_tab);
    window.draw(stats_tab);

    switch(inventory->Get_current_tab())
    {
        case InventoryTab::items:
            Render_items(size,font);
            break;
        case InventoryTab::equipment:
            Render_equipment(size,font);
            break;
        case InventoryTab::stats:
            Render_stats(size,font);
            break;
    }

    Set_view();
}

void conor::Graphics_manager::Render_items(sf::Vector2u size, sf::Font font)
{
    auto inventory = assign_player->Get_const_inventory();
    auto items = inventory->Get_items();

    float ITEM_SPACING = 60.f;
    float LEFT_MARGIN = (size.x*0.2) + 20.f;
    float TOP_MARGIN = (size.y*0.2) + 100.f;

    sf::Texture tmp{};
    float y_offset = TOP_MARGIN;
    for(int i=0; i< items.size(); i++)
    {
        auto item = items[i].lock();
        if(!item) continue;

        sf::Sprite icon{tmp};
        item_storage.Set_item_to_sptite(icon,item);
        icon.setPosition( {LEFT_MARGIN,y_offset} );
        icon.setScale( {4.0f,4.0f} );
        window.draw(icon);

        sf::Text item_name{font,item->Get_name(),20};

        if(i == inventory->Get_selected_item_index())
        {
            item_name.setStyle(sf::Text::Bold);
            item_name.setFillColor(sf::Color(255, 255, 150));
        }
        else
        {
            item_name.setFillColor(sf::Color::White);
        }

        item_name.setPosition( {LEFT_MARGIN + 16*4 + 12.f, y_offset - 2.f} );
        window.draw(item_name);

        sf::Text item_discription{font,item->Get_discription(),14};
        item_discription.setFillColor(sf::Color{200,200,200});
        item_discription.setPosition( {LEFT_MARGIN + 16*4 + 12.f, y_offset + 18.f} );
        window.draw(item_discription);

        y_offset += ITEM_SPACING;
    }
}

void conor::Graphics_manager::Render_equipment(sf::Vector2u size, sf::Font font)
{
    auto armor = assign_player->Get_const_armor();
    auto weapon = assign_player->Get_const_weapon();

    float ITEM_SPACING = 100.f;
    float LEFT_MARGIN = (size.x*0.2) + 20.f;
    float TOP_MARGIN = (size.y*0.2) + 80.f;

    sf::Texture tmp{};
    sf::Sprite icon{tmp};
    icon.setScale( {4.0,4.0} );
    float y_offset = TOP_MARGIN;

    sf::Text armor_info{font,"Armor: ",40};
    armor_info.setPosition( {LEFT_MARGIN + 12.f, y_offset - 2.f} );

    sf::Text armor_name{font,"None",40};
    armor_name.setPosition( {LEFT_MARGIN + 150.f +  4*16.f, y_offset - 2.f} );
    armor_name.setFillColor(sf::Color{40,40,40});
    if(armor)
    {
        armor_name.setString( armor->Get_name() );
        item_storage.Set_item_to_sptite(icon, armor);
        icon.setPosition( {LEFT_MARGIN + 150.f, y_offset - 6.f} );
        window.draw(icon);
    }
    window.draw(armor_name);

    y_offset += ITEM_SPACING;
    sf::Text weapon_info{font,"Weapon:",40};
    weapon_info.setPosition( {LEFT_MARGIN + 12.f, y_offset - 2.f} );

    sf::Text weapon_name{font,"None",40};
    weapon_name.setPosition( {LEFT_MARGIN + 170.f +  4*16.f, y_offset - 2.f} );
    weapon_name.setFillColor(sf::Color{40,40,40});
    if(weapon)
    {
        weapon_name.setString( weapon->Get_name() );
        item_storage.Set_item_to_sptite(icon, weapon);
        icon.setPosition( {LEFT_MARGIN + 150.f, y_offset - 6.f} );
        window.draw(icon);
    }
    window.draw(weapon_name);

    auto inventory = assign_player->Get_const_inventory();
    switch(inventory->Get_selected_equipment_index())
    {
        case 0:
            armor_info.setStyle(sf::Text::Bold);
            armor_info.setFillColor(sf::Color(255, 255, 150));
            break;
        case 1:
            weapon_info.setStyle(sf::Text::Bold);
            weapon_info.setFillColor(sf::Color(255, 255, 150));
            break;
    }

    window.draw(armor_info);
    window.draw(weapon_info);
}

void conor::Graphics_manager::Render_stats(sf::Vector2u size, sf::Font font)
{
    auto stats = assign_player->stats;

    float ITEM_SPACING = 90.f;
    float LEFT_MARGIN = (size.x*0.2) + 20.f;
    float TOP_MARGIN = (size.y*0.2) + 80.f;

    float y_offset = TOP_MARGIN;

    sf::Text stats_text{font,"Attack: " + std::to_string(stats.atack),35};
    stats_text.setPosition( {LEFT_MARGIN + 12.f, y_offset - 2.f} );
    stats_text.setFillColor(sf::Color::Blue);
    window.draw(stats_text);

    y_offset += ITEM_SPACING;

    stats_text.setString("Defence: " + std::to_string(stats.defence));
    stats_text.setPosition( {LEFT_MARGIN + 12.f, y_offset - 2.f} );
    stats_text.setFillColor(sf::Color::Blue);
    window.draw(stats_text);

    y_offset += ITEM_SPACING;

    stats_text.setString("Speed: " + std::to_string(stats.speed));
    stats_text.setPosition( {LEFT_MARGIN + 12.f, y_offset - 2.f} );
    stats_text.setFillColor(sf::Color::Blue);
    window.draw(stats_text);
}

void conor::Graphics_manager::Update()
{
    // sf::View view = window.getView();
    //
    // view.setCenter( {map.player_possition.x, map.player_possition.y} );
    //
    // window.setView( view );
    //

    //TO FIX!
}

void conor::Graphics_manager::onNotify(Event event, std::shared_ptr<Being> &entity)
{
    switch(event)
    {
        case Event::Player_moved:
            sf::Vector2u size = window.getSize();
            if(entity->possition.x >= render_area_end.x)
            {
                render_area_end.x += static_cast<int> (size.x/100);
                render_area_start.x += static_cast<int> (size.x/100);
            }
            else if(entity->possition.x < render_area_start.x)
            {
                render_area_end.x -= static_cast<int> (size.x/100);
                render_area_start.x -= static_cast<int> (size.x/100);
            }
            else if(entity->possition.y >= render_area_end.y)
            {
                render_area_end.y += static_cast<int>(size.y/100);
                render_area_start.y += static_cast<int>(size.y/100);
            }
            else if(entity->possition.y < render_area_start.y)
            {
                render_area_end.y -= static_cast<int>(size.y/100);
                render_area_start.y -= static_cast<int>(size.y/100);
            }

            break;
    }
}

void conor::Graphics_manager::Set_path_to_enemies_stats(std::string path_to_enemies)
{
    Board_generator::path_to_enemies_stats = path_to_enemies;
}

void conor::Graphics_manager::Set_player(std::shared_ptr<Player>& player)
{
    assign_player = player;
}

