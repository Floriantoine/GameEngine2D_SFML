#pragma once

#include "./Observer.hpp"
#include "./Subject.hpp"
#include "EventType.hpp"
#include "stdio.h"

#include <vector>

class ObserverManager : public IObserver {
  private:
    std::vector<std::pair<Observer *, EventType>> _observers;
    std::vector<std::pair<Subject *, EventType>> _subjects;
    std::string message_from_subject_;

  public:
    ObserverManager(Subject *subject) = delete;

    void Update(EventType eventType, const std::string &msg) override
    {
        message_from_subject_ = msg;
        std::cout << "message: " << msg << std::endl;

        for (const auto &ob: _observers) {
            if (ob.second == eventType) {
                ob.first->Update(eventType, msg);
            }
        }
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------

    void addObserver(Observer *observer, EventType type)
    {
        this->_observers.push_back(
            std::pair<Observer *, EventType>(observer, type));
    };

    void addSubject(Subject *subject, EventType type)
    {
        this->_subjects.push_back(
            std::pair<Subject *, EventType>(subject, type));

        subject->Attach(this);
    }
    ObserverManager(/* args */) = default;
    ~ObserverManager() = default;
};
