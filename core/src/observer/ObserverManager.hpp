#pragma once

#include "./Observer.hpp"
#include "./Subject.hpp"
#include "EventType.hpp"
#include "stdio.h"

#include <vector>

class ObserverManager {
  private:
    std::vector<std::pair<Observer *, EventType>> _observers;
    std::vector<std::pair<Subject *, EventType>> _subjects;

  public:
    void addObserver(Observer *observer, EventType type)
    {
        this->_observers.push_back(
            std::pair<Observer *, EventType>(observer, type));

        for (const auto &ob: _subjects) {
            if (ob.second == type) {
                observer->setSubject(ob.first);
            }
        }
    };

    void addSubject(Subject *subject, EventType type)
    {
        this->_subjects.push_back(
            std::pair<Subject *, EventType>(subject, type));

        for (const auto &ob: _observers) {
            if (ob.second == type) {
                ob.first->setSubject(subject);
            }
        }
    }
    ObserverManager(/* args */) = default;
    ~ObserverManager() = default;
};
