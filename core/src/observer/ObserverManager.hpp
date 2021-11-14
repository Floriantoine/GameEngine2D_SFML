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

  public:
    ObserverManager(Subject *subject) = delete;

    void handle(Event const &event) override
    {
        std::cout << "aa" << std::endl;
        std::vector<Observer *>::iterator iterator = _observers.begin();
        std::cout << "size: " << std::endl;

        while (iterator != _observers.end()) {
            std::cout << "cc" << std::endl;
            if ((*iterator) != nullptr && (*iterator) != NULL) {
                std::cout << "av" << std::endl;
                (*iterator)->handle(event);
                std::cout << "22" << std::endl;
            }
            ++iterator;
        }
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------

    void addObserver(Observer *observer)
    {
        if (observer == nullptr)
            return;
        this->_observers.push_back(observer);
    };

    void deleteObserver(Observer *observer)
    {
        auto it = std::find(_observers.begin(), _observers.end(), observer);

        if (it != _observers.end())
            _observers.erase(it);
    };

    void addSubject(Subject *subject)
    {
        this->_subjects.push_back(subject);

        subject->Attach(this);
    }
    ObserverManager(/* args */) = default;
    ~ObserverManager()
    {
        _observers.clear();
        _subjects.clear();
    };
};
