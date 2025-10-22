#include "./subject.hpp"

void conor::Subject::Notify(Event event)
{
    for(auto observer : observers)
        observer->onNotify(event);
}

void conor::Subject::Add_observer(Observer* observer)
{
    for(int i=0;i<observers.size();i++)
    {
        if(observers[i] == observer)
            return;
    }
    observers.push_back(observer);
}

void conor::Subject::Remove_observer(Observer* observer)
{
    for(int i=0;i<observers.size();i++)
    {
        if(observers[i] == observer)
            observers.erase( observers.begin() + i );
    }
}

