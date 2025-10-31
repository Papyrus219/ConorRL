#ifndef CONOR_GAME_HPP
#define CONOR_GAME_HPP

#include "./system/graphics/graphics_manager.hpp"
#include "./system/resorces_manager.hpp"
#include "./system/logic/loop_manager.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Game
{
public:
    void Setup();
    void Start();

private:
    Graphics_manager renderer{};
    Loop_manager looper{};
    Resorces_manager resorcer{};
};

}

#endif // CONOR_GAME_HPP
