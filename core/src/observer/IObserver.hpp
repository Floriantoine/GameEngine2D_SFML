#pragma once

#include <iostream>
#include <list>
#include <string>

class IObserver {
  public:
    virtual ~IObserver(){};
    virtual void Update(const std::string &message_from_subject) = 0;
};