#include "enemies_manager.hpp"

using namespace conor;

void conor::Enemies_manager::Add_enemy(std::shared_ptr<Enemy>& enemy)
{
    for(auto &en : enemies)
        if(en == enemy) return;

    enemies.push_back(enemy);
}

void conor::Enemies_manager::Remove_enemy(std::shared_ptr<Enemy>& enemy)
{
    for(auto it = enemies.begin(); it != enemies.end();)
    {
        if(*it == enemy)
            it = enemies.erase(it);
        else
            it++;
    }
}

std::vector<std::weak_ptr<Enemy>> conor::Enemies_manager::Get_enemies()
{
    std::vector< std::weak_ptr<Enemy> > converted{};

    for(auto &enemy : enemies)
        converted.emplace_back( enemy );

    return converted;
}

void conor::Enemies_manager::onNotify(Event event, std::shared_ptr<Being> &entity)
{
    switch(event)
    {
        case Event::Enemy_killed:
            std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(entity);
            Remove_enemy(enemy);
            break;
    }
}
