#ifndef CONOR_OBSERVER_HPP
#define CONOR_OBSERVER_HPP

#include "./event.hpp"
#include "../being/being.hpp"

namespace conor
{

class Observer
{
public:
    virtual void onNotify(Event event, std::shared_ptr<Being> entity) = 0;
    virtual ~Observer();
};

}

#endif
