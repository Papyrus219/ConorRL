#ifndef CONOR_OBSERVER_HPP
#define CONOR_OBSERVER_HPP

#include "./event.hpp"

namespace conor
{

class Observer
{
public:
    virtual void onNotify(Event event);
    virtual ~Observer();
};

}

#endif
