#ifndef CONOR_PATH_FINDER_HPP
#define CONOR_PATH_FINDER_HPP

#include "../../board/board.hpp"
#include "../../tools/observer.hpp"
#include "../../tools/subject.hpp"

namespace conor {

class Player;
class Enemy;
class Subject;

/**
 * @todo write docs
 */
class Path_finder: public Observer
{
public:
    Path_finder() = default;
    Path_finder(Board* board, std::vector< std::shared_ptr<Enemy> > *enemies);

    void Set_board(Board* board);
    void Set_enemies(std::vector< std::shared_ptr<Enemy> > *enemies);
    void Update_distances(std::shared_ptr<Player> player);
    void Move_enemies();
    void onNotify(Event event, std::shared_ptr<Being> &entity) override;

    Subject subject{};
private:
    Board* assign_board{};
    std::vector< std::vector<int> > distans{};
    std::vector< std::shared_ptr<Enemy> > *assign_enemies{};
};

}

#endif // CONOR_PATH_FINDER_HPP
