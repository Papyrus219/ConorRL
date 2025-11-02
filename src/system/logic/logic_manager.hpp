#ifndef CONOR_LOOP_MANAGER_HPP
#define CONOR_LOOP_MANAGER_HPP

#include <optional>
#include <memory>
#include "./path_finder.hpp"
#include "./game_state.hpp"
#include "../../player/input/input_handler.hpp"
#include "../../tools/observer.hpp"

namespace conor {

class Game;
class Resorces_manager;
class Graphics_manager;

/**
 * @todo write docs
 */
class Logic_manager: public Observer
{
public:
    void Loop();
    virtual void onNotify(Event event, std::shared_ptr<Being> &entity) override;

    Game_state game_state{Game_state::main_menu};
    std::optional<Path_finder> path_finder{};
    std::optional<Input_handler> input_handler{};

private:
    std::shared_ptr<Resorces_manager> resorcer{};
    std::shared_ptr<Graphics_manager> renderer{};

    void Events();

    friend class Game;
};

}

#endif // CONOR_LOOP_MANAGER_HPP
