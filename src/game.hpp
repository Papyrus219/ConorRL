#ifndef CONOR_GAME_HPP
#define CONOR_GAME_HPP

#include <memory>
#include "./system/graphics/graphics_manager.hpp"
#include "./system/resorces/resorces_manager.hpp"
#include "./system/logic/logic_manager.hpp"
#include "./system/audio/audio_manager.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Game
{
public:
    void Start();

private:
    void Setup();

    std::shared_ptr<Graphics_manager> renderer{};
    std::shared_ptr<Logic_manager> looper{};
    std::shared_ptr<Resorces_manager> resorcer{};
    std::shared_ptr<Audio_manager> audier{};
};

}

#endif // CONOR_GAME_HPP
