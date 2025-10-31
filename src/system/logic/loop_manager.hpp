#ifndef CONOR_LOOP_MANAGER_H
#define CONOR_LOOP_MANAGER_H

#include <optional>
#include "./path_finder.hpp"

namespace conor {

/**
 * @todo write docs
 */
class Loop_manager
{
public:

    std::optional<Path_finder> path_finder{};
};

}

#endif // CONOR_LOOP_MANAGER_H
