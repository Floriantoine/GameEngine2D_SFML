#pragma once

#include "./Observer.hpp"
#include "./Subject.hpp"
#include "EventType.hpp"
#include "stdio.h"

#include <vector>

class ObserverManager : public IObserver {
  private:
    std::vector<Observer *> _observers;
    std::vector<Subject *> _subjects;
    std::string message_from_subject_;

  public:
    ObserverManager(Subject *subject) = delete;

    void handle(Event const &event) override
    {
        std::vector<Observer *>::iterator iterator = _observers.begin();

        while (iterator != _observers.end()) {
            (*iterator)->handle(event);
            ++iterator;
        }
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------

    void addObserver(Observer *observer)
    {
        this->_observers.push_back(observer);
    };

    void addSubject(Subject *subject)
    {
        this->_subjects.push_back(subject);

        subject->Attach(this);
    }
    ObserverManager(/* args */) = default;
    ~ObserverManager() = default;
};
