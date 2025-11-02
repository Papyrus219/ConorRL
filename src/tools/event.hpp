#ifndef CONOR_EVENT_HPP
#define CONOR_EVENT_HPP

namespace conor
{
    enum class Event
    {
        Game_started=0,
        Player_moved=1,
        Enemy_killed=2,
        Enemy_attack=3,
        Player_atack=4
    };
}

#endif
