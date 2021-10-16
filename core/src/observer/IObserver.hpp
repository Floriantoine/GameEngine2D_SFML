#pragma once

#include <iostream>
#include <list>
#include <string>

#include "EventType.hpp"

class IObserver {
  public:
    virtual ~IObserver(){};
    virtual void Update(EventType eventType, const std::string &msg) = 0;
};