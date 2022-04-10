#pragma once

#include <iostream>
#include <list>
#include <string>

#include "EventType.hpp"

class IObserver {
  public:
    virtual ~IObserver(){};
    virtual void handle(Event const &event) = 0;
};