#pragma once

#include "./Observer.hpp"
#include "./Subject.hpp"
#include "EventType.hpp"
#include "stdio.h"

#include <vector>

class ObserverManager : public IObserver {
  private:
    std::vector<Observer *> _observers;
    std::vector<Observer *> _observerQueue;
    std::vector<Subject *> _subjects;

  public:
    ObserverManager(Subject *subject) = delete;

    void handle(Event const &event) override
    {
        if (_observerQueue.size() > 0) {
            _observers.insert(
                _observers.end(), _observerQueue.begin(), _observerQueue.end());
            _observerQueue.clear();
        }

        std::vector<Observer *>::iterator iterator = _observers.begin();
        while (iterator != _observers.end()) {
            if ((*iterator) != nullptr && (*iterator) != NULL) {
                (*iterator)->handle(event);
                ++iterator;
            } else {
                _observers.erase(iterator);
            }
        }
    }

    void clear()
    {
        _observerQueue.clear();
        _observers.clear();
        _subjects.clear();
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    int observerCount() const
    {
        return _observers.size() + _observerQueue.size();
    };

    int subjectCount() const
    {
        return _subjects.size();
    }

    void addObserver(Observer *observer)
    {
        if (observer == nullptr)
            return;
        this->_observerQueue.push_back(observer);
    };

    void deleteObserver(Observer *observer)
    {
        auto it = std::find(_observers.begin(), _observers.end(), observer);

        if (it != _observers.end())
            _observers.erase(it);
        else {
            auto it = std::find(
                _observerQueue.begin(), _observerQueue.end(), observer);

            if (it != _observerQueue.end())
                _observerQueue.erase(it);
        }
    };

    void deleteSubject(Subject *subject)
    {
        auto it = std::find(_subjects.begin(), _subjects.end(), subject);

        if (it != _subjects.end())
            _subjects.erase(it);
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
        _observerQueue.clear();
    };
};
