#ifndef CONOR_ENEMIES_MANAGER_HPP
#define CONOR_ENEMIES_MANAGER_HPP

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
public:
    Enemies_manager() = default;

    void Add_enemy( std::shared_ptr<Enemy> &enemy );
    void Remove_enemy( std::shared_ptr<Enemy> &enemy );
    std::vector< std::weak_ptr<Enemy> > Get_enemies();
    std::vector< std::shared_ptr<Enemy> >* Get_enemies_ptr() {return &enemies;};
    void onNotify(Event event, std::shared_ptr<Being> &entity) override;

private:
    std::vector< std::shared_ptr<Enemy> > enemies{};
};

}

#endif // CONOR_ENEMIES_MANAGER_HPP
