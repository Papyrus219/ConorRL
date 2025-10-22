#ifndef CONOR_SUBJECT_HPP
#define CONOR_SUBJECT_HPP

#include <vector>
#include "./observer.hpp"

namespace conor
{

class Subject
{
public:
        void Notify(Event event);
        void Add_observer(Observer *observer);
        void Remove_observer(Observer *observer);
private:
    std::vector<Observer*> observers;
};

}

#endif
