
#pragma once

#include "./IObserver.hpp"
#include <iostream>
#include <list>
#include <string>

class ISubject {
  public:
    virtual ~ISubject(){};
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify(EventType event) = 0;
};
