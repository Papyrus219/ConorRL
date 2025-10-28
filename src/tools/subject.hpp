#ifndef CONOR_SUBJECT_HPP
#define CONOR_SUBJECT_HPP

#include <vector>
#include <memory>
#include "./event.hpp"

namespace conor
{

class Observer;
struct Being;

class Subject
{
public:
        void Notify(Event event, std::shared_ptr<Being> &entity);
        void Add_observer(Observer *observer);
        void Remove_observer(Observer *observer);
private:
    std::vector<Observer*> observers;
};

}

#endif
