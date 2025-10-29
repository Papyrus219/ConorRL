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
                std::cout << "Halo: " << y << " " << x << "\n";
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
    window.setView( window.getDefaultView() );
    sf::Vector2u size = window.getSize();

    sf::RectangleShape background({size.x*0.6f, size.y*0.6f});
    background.setFillColor(sf::Color{128,10,10,150});
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(4.f);

    background.setPosition({size.x*0.2f, size.y*0.2f});
    window.draw(background);

    sf::Font font;
    if(font.openFromFile("../../data/fonts/font1.ttf"))
    {
        sf::Text title{font,"Inventory",35};
        title.setFillColor(sf::Color::White);
        title.setPosition( {size.x*0.22f, size.y * 0.22f} );
        window.draw(title);
    }
    else
    {
        std::cerr << "Jesteś na steam decku!\n";
    }

    Set_view();
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

