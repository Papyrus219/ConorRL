#ifndef CONOR_LOOP_MANAGER_HPP
#define CONOR_LOOP_MANAGER_HPP

#include <optional>
#include <memory>
#include "./path_finder.hpp"
#include "../../player/input/input_handler.hpp"

namespace conor {

class Game;
class Resorces_manager;
class Graphics_manager;

/**
 * @todo write docs
 */
class Logic_manager
{
public:
    void Loop();

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
