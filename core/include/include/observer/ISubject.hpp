
#pragma once

#include "./IObserver.hpp"
#include "EventType.hpp"
#include <iostream>
#include <list>
#include <string>

class ISubject {
  public:
    virtual ~ISubject(){};
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify(Event const &event) = 0;
};
