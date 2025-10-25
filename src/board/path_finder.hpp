#ifndef CONOR_PATH_FINDER_HPP
#define CONOR_PATH_FINDER_HPP

#include "./board.hpp"
#include "../player/player.hpp"
#include "../enemies/enemy.hpp"
#include "../tools/observer.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Path_finder: public Observer
{
public:
    Path_finder() = default;
    Path_finder(Board* board, std::vector<Enemy*> &enemies);

    void Set_board(Board* board);
    void Set_enemies(std::vector<Enemy*> &enemies);
    void Update_distances(Player* player);
    void Move_enemies();
    void onNotify(Event event, Being * entity) override;

private:
    Board* assign_board{};
    std::vector< std::vector<int> > distans{};
    std::vector<Enemy*> *assign_enemies{};
};

}

#endif // CONOR_PATH_FINDER_HPP
