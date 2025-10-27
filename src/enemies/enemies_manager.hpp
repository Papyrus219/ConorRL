#ifndef CONOR_ENEMIES_MANAGER_H
#define CONOR_ENEMIES_MANAGER_H

#include <vector>
#include <memory>
#include "./enemy.hpp"
#include "../tools/observer.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Enemies_manager: public Observer
{
    std::vector< std::weak_ptr<Enemy> > Get_enemies();
    void Add_enemy( std::shared_ptr<Enemy> &enemy );
    void Remove_enemy( std::shared_ptr<Enemy> &enemy );
    void onNotify(Event event, std::shared_ptr<Being> entity) override;
private:
    std::vector< std::shared_ptr<Enemy> > enemies{};
};

}

#endif // CONOR_ENEMIES_MANAGER_H
