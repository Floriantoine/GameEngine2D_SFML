
#pragma once
#include "./ISubject.hpp"

class Subject : public ISubject {
  public:
    virtual ~Subject()
    {
    }

    /**
     * The subscription management methods.
     */
    void Attach(IObserver *observer) override
    {
        list_observer_.push_back(observer);
    }
    void Detach(IObserver *observer) override
    {
        list_observer_.remove(observer);
    }

    void Notify(Event const &event) override
    {
        std::list<IObserver *>::iterator iterator = list_observer_.begin();
        while (iterator != list_observer_.end()) {
            (*iterator)->handle(event);
            ++iterator;
        }
    }

    void CreateMessage(Event const &event)
    {
        Notify(event);
    }

  private:
    std::list<IObserver *> list_observer_;
};